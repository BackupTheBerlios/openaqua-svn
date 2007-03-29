package de.openaqua.regtest;

import java.util.List;

import org.apache.log4j.Logger;
import org.springframework.beans.factory.access.BeanFactoryLocator;
import org.springframework.beans.factory.access.BeanFactoryReference;
import org.springframework.beans.factory.access.SingletonBeanFactoryLocator;

import de.openaqua.dev.entities.Country;
import de.openaqua.dev.entities.CountryDao;
import de.openaqua.dev.entities.PhoneFormatDao;
import de.openaqua.dev.exception.ServiceException;
import de.openaqua.dev.services.CountryCriteria;
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
		
		logger.warn("=====================List all Countries=====================");
		
		CountryVO[] vos =  cs.getAllCountries();
		if (vos == null) {
			logger.warn("Array vos is empty");
		}

		for (int i = 0; i< vos.length; ++i) {
			CountryVO v = vos[i];
			logger.warn("Found Country with ISO "+ v.getIso() + " and name " + v.getDescription());
		}
	}
	
	
	
	/*
	List countries = getCountryDao().findByCriteria(criteria);
	getCountryDao().toCountryVOCollection(countries);
	return (CountryVO[]) (countries.toArray(new CountryVO[0]));
	*/
	
	public CountryVO getCountry(final String iso, final String name) throws ServiceException {
		BeanFactoryLocator bfl = SingletonBeanFactoryLocator.getInstance();
		BeanFactoryReference bf = bfl.useBeanFactory("beanRefFactory");
		
		CountryService cs = (CountryService) bf.getFactory().getBean("countryService");
		CountryCriteria criteria =new CountryCriteria();
		criteria.setIso("DE");
		CountryVO[] results = cs.findCountriesByCriteria(criteria);
		if (results.length == 0) {
			CountryDao cdao = (CountryDao) bf.getFactory().getBean("countryDao");
			logger.warn("create Country " + iso + " and desc "+ name);
			return cdao.toCountryVO(cdao.create(iso, name, ""));
		} else {
			logger.warn("found Country " + results[0].getIso());
			return results[0];
		}
	}
	
	
	
	public void mainTest() throws ServiceException {
		logger.info(" ===================== Run Spring Test =====================");
		
		//BeanFactoryLocator bfl = SingletonBeanFactoryLocator.getInstance();
		//BeanFactoryReference bf = bfl.useBeanFactory("beanRefFactory");
		//PhoneFormatDao phone = (PhoneFormatDao) bf.getFactory().getBean("phoneFormatDao");
		//phone.create("*");

		listAllCountries();
		
		CountryVO de = getCountry("DE", "Germany");
		CountryVO us = getCountry("US", "United States");
		CountryVO uk = getCountry("UK", "United Kingdom");

		listAllCountries();
		
		
		if (de == null) 	logger.error("Error with country de");
		if (us == null) 	logger.error("Error with country us");
		if (uk == null) 	logger.error("Error with country uk");
	
	}

}
