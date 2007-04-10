/**
 * 
 */
package de.openaqua.regTestHelper;

import java.util.Timer;
import org.apache.log4j.Logger;
import org.springframework.beans.factory.access.BeanFactoryLocator;
import org.springframework.beans.factory.access.BeanFactoryReference;
import org.springframework.beans.factory.access.SingletonBeanFactoryLocator;






/**
 * @author behrenan
 *
 */
public abstract class LoadGenerator extends Thread{
	final boolean doReadTest;
	private final static Logger logger = Logger.getRootLogger();
	final private BeanFactoryLocator bfl = SingletonBeanFactoryLocator.getInstance();
	final private BeanFactoryReference bf = bfl.useBeanFactory("beanRefFactory");
	

	/**
	 * Constructor
	 */
	public LoadGenerator(boolean readTest, String threadName)  {
		super( threadName); 
		doReadTest = readTest;
		System.out.println("Thread " + threadName + " created");
	}

	
	/*
	 * sample:
	 * 
	 * <code>
	 * 	public LoadGenerator getNewInstance(boolean readTest, String threadName)
	{
		return new AlmaLoadGenerator(readTest, threadName);		
	}
	</code>
	 */
	public abstract LoadGenerator getNewInstance(boolean readTest, String threadName);

	public abstract boolean executeRead();
	public abstract boolean executeWrite();

	public abstract boolean setupEnvironment();
	public abstract boolean cleanEnvironment();


	protected final BeanFactoryReference getBeanFactory() {
		return bf;
	}
	
	protected final void printError(Exception e) {
		logger.error("Message: "+e.getMessage());
		e.printStackTrace();
		
	}

	
	/**
	 * The thread execution method
	 * runs endless
	 */
	final public void run () {
		for (int i = 0; i < RegTestConfiguration.getInstance().getReqLoops(); i++){
			if (doReadTest) {
				executeRead();				
				RegTestStats.getInstance().addReadResults(1);
			} else {
				executeWrite();				
				RegTestStats.getInstance().addWriteResults(1);
			}
		}

	}


	final public boolean fireUpLoadTest() {
		final Logger logger = Logger.getRootLogger();
		logger.info( "Start Load Test with " + RegTestConfiguration.getInstance().getMaxConnections()+" Threads" );
		
		
		//setup enironment
		if (cleanEnvironment() == false 
				|| setupEnvironment() == false) {
			logger.error("Setting up environment went wrong");
			return false;
		}
		
		
		//setup threads
		final LoadGenerator[] threadArray = new LoadGenerator[RegTestConfiguration.getInstance().getMaxConnections()];

		int readInstance = 0;
		int writeInstance = 0;

		for (int i = 0; i < RegTestConfiguration.getInstance().getMaxConnections(); i++) {
			if (i%2==1) {		
				threadArray[i] = getNewInstance(true, ""+i);
				readInstance++;
			}else {
				threadArray[i] = getNewInstance(false, ""+i);
				writeInstance++;
			}
		}
		logger.info("Read  Access Threads: " + readInstance);
		logger.info("Write Access Threads: " + writeInstance);
		
		//fire up test
		//and do the measuring stuff
		long runTime = 0;
		Timer timer = new Timer();
		try {
			int count = RegTestConfiguration.getInstance().getStatsAllMilliseconds();
			timer.schedule(new MinuteTimer(count), count, count);
			long start = System.currentTimeMillis();

			//fire the loader up
			for (int i = 0; i < RegTestConfiguration.getInstance().getMaxConnections(); i++) 	threadArray[i].start();
			
			//wait for finish
			for (int i = 0; i < RegTestConfiguration.getInstance().getMaxConnections(); i++) {
				try {
					threadArray[i].join();
				} catch (InterruptedException e) {
					logger.error("Error while joining a thread");
					e.printStackTrace();
				}
			}
			
			
			runTime = System.currentTimeMillis() - start;
		} finally {
			timer.cancel();
		}

		logger.info( "Runtime was " +runTime + "ms");
		
		return true;
	}
}
