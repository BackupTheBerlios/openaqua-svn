package de.openaqua.regtest;

import org.apache.log4j.Logger;
import org.springframework.beans.factory.access.BeanFactoryLocator;
import org.springframework.beans.factory.access.BeanFactoryReference;
import org.springframework.beans.factory.access.SingletonBeanFactoryLocator;

import de.openaqua.dev.entities.CountryDao;
import de.openaqua.dev.entities.PhoneFormatDao;
import de.openaqua.dev.exception.ServiceException;
import de.openaqua.dev.services.CountryService;
import de.openaqua.dev.vo.CountryVO;

public class SpringTest {
	private final static Logger logger = Logger.getRootLogger();
	
	public SpringTest () {
		super();
	}
	
	public void listAllCountries() throws ServiceException {
		BeanFactoryLocator bfl = SingletonBeanFactoryLocator.getInstance();
		BeanFactoryReference bf = bfl.useBeanFactory("beanRefFactory");
		//CountryDao cdao = (CountryDao) bf.getFactory().getBean("countryDao");
		CountryService cs = (CountryService) bf.getFactory().getBean("countryService");
		
		CountryVO[] vos =  cs.getAllCountries();
		if (vos == null) {
			logger.error("Array vos is empty");
			
		}
		for (int i = 0; i< vos.length; ++i) {
			CountryVO v = vos[i];
			logger.info("Found Country with ISO "+ v.getIso());
		}


	}
	
	public CountryVO getCountry(final String iso, final String name) throws ServiceException {
		BeanFactoryLocator bfl = SingletonBeanFactoryLocator.getInstance();
		BeanFactoryReference bf = bfl.useBeanFactory("beanRefFactory");
		CountryDao cdao = (CountryDao) bf.getFactory().getBean("countryDao");
		CountryService cs = (CountryService) bf.getFactory().getBean("countryService");
		
		//breaks since getCountryByIso still not implemented 
		if (cs.getCountryByIso(iso) == null) {
			cdao.create(iso, name, "");
			
			logger.info("created country for iso " + iso);
			
		}
		return cs.getCountryByIso(iso);
	}
	
	public void mainTest() throws ServiceException {
		logger.info(" ===================== Run Spring Test =====================");
		
		BeanFactoryLocator bfl = SingletonBeanFactoryLocator.getInstance();
		BeanFactoryReference bf = bfl.useBeanFactory("beanRefFactory");
		PhoneFormatDao phone = (PhoneFormatDao) bf.getFactory().getBean("phoneFormatDao");
		phone.create("*");
		
		CountryVO de = getCountry("DE", "Germany");
		CountryVO us = getCountry("US", "United States");
		CountryVO uk = getCountry("UK", "United Kingdom");
		
		listAllCountries();
		
		if (de == null) 	logger.error("Error with country de");
		if (us == null) 	logger.error("Error with country us");
		if (uk == null) 	logger.error("Error with country uk");

		
	}

}
