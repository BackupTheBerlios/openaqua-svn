package de.openaqua.regtest;

import org.apache.log4j.Logger;
import org.springframework.beans.factory.access.BeanFactoryLocator;
import org.springframework.beans.factory.access.BeanFactoryReference;
import org.springframework.beans.factory.access.SingletonBeanFactoryLocator;

import de.openaqua.dev.services.CountryService;

public class SpringTest {
	private final static Logger logger = Logger.getRootLogger();
	
	public SpringTest () {
		super();
	}
	
	public void mainTest() {
		logger.info(" ===================== Run Spring Test =====================");
		
		BeanFactoryLocator bfl = SingletonBeanFactoryLocator.getInstance();
		BeanFactoryReference bf = bfl.useBeanFactory("beanRefFactory");
		CountryService cs = (CountryService) bf.getFactory().getBean("countryService");
		
	}

}
