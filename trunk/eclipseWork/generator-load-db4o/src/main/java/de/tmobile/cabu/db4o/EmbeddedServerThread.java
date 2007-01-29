/**
 * 
 */
package de.tmobile.cabu.db4o;

import org.apache.log4j.Logger;

import com.db4o.Db4o;
import com.db4o.ObjectContainer;
import com.db4o.ObjectServer;


/**
 * @author behrenan
 *
 */
final public class EmbeddedServerThread implements Runnable{
	private boolean stop;
	final private static Logger logger = Logger.getRootLogger();
	final private EmbeddedServerConfiguration configuration;
	private ObjectServer db4oServer;


	
	public EmbeddedServerThread (final EmbeddedServerConfiguration configuration) {
		super();
		this.stop = false;
		this.configuration = configuration;
		this.db4oServer.ext().configure().lockDatabaseFile(true);
		this.db4oServer = Db4o.openServer(this.configuration.getFilename(), 0);
	}


	public String getDatabaseFilename() {
		return configuration.getFilename();
	}
	
	
	public void run() {
		synchronized(this){

			Thread.currentThread().setName(this.getClass().getName());
			Thread.currentThread().setPriority(Thread.MIN_PRIORITY); //db4oserver has its own thread
			
			try {
				logger.info("Start Server");
				if(!stop) this.wait(Long.MAX_VALUE); // wait forever for notify() from close()   
			} catch (Exception e) {
				logger.error(e.getLocalizedMessage());
				e.printStackTrace();
			}
			
			db4oServer.close();
		}
	}
	
	public ObjectContainer getClient() {
		ObjectContainer result = null;
		synchronized(this){
			result = db4oServer.openClient();
		}
		return result;
	}
	


	public void close(){
		synchronized(this){
			logger.info("Close Server");
			stop = true;
			this.notify();
		}
	}
}	

