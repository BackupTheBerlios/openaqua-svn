package de.openaqua.regtest;



import org.apache.log4j.Logger;
import org.springframework.beans.factory.access.BeanFactoryLocator;
import org.springframework.beans.factory.access.BeanFactoryReference;
import org.springframework.beans.factory.access.SingletonBeanFactoryLocator;



public class RegTest {
	
	private final static Logger logger = Logger.getRootLogger();
	private BeanFactoryLocator bfl = SingletonBeanFactoryLocator.getInstance();
	private BeanFactoryReference bf = bfl.useBeanFactory("beanRefFactory");

	private RegTest(){super();};
	
	
	public RegTest(final String name) {
		logger.info("start --------------" + name + "---------------");
		
	}
	
	
	public boolean RunTest(){
		return false;		
	}

	protected static final Logger logger() {
		return logger;
	}
	
	protected static final Logger getLogger() {
		return logger;
	}

	protected final BeanFactoryReference getBeanFactory() {
		return bf;
	}
	
	protected final void printError(Exception e) {
		logger.error("Message: "+e.getMessage());
		e.printStackTrace();
		
	}
	
}
