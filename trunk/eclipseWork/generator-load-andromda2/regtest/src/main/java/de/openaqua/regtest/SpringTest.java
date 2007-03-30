package de.openaqua.regtest;

import java.util.Iterator;
import java.util.List;

import org.apache.log4j.Logger;
import org.springframework.beans.factory.access.BeanFactoryLocator;
import org.springframework.beans.factory.access.BeanFactoryReference;
import org.springframework.beans.factory.access.SingletonBeanFactoryLocator;

import de.openaqua.dev.entities.Country;
import de.openaqua.dev.entities.CountryDao;
import de.openaqua.dev.entities.PhoneFormatDao;
import de.openaqua.dev.entities.crud.CountryManageableDao;
import de.openaqua.dev.exception.ServiceException;
import de.openaqua.dev.services.CountryCriteria;
import de.openaqua.dev.services.CountryService;
import de.openaqua.dev.vo.CountryVO;


public class SpringTest {
	private final static Logger logger = Logger.getRootLogger();
	
	
	public SpringTest () {
		super();
	}
	
	
	public void listAllCountries() {
		
		BeanFactoryLocator bfl = SingletonBeanFactoryLocator.getInstance();
		BeanFactoryReference bf = bfl.useBeanFactory("beanRefFactory");
		CountryManageableDao dao = (CountryManageableDao) bf.getFactory().getBean("CountryManageableDao");
		List list = dao.readAll();
		
		logger.warn("=====================List all Countries=====================");
		if (list.isEmpty()) {
			logger.error("List of all countries is empty");
		} else {
			Iterator iter = list.iterator();
			while(iter.hasNext()) {
				Country c  = (Country) iter.next();
				logger.warn("Found Country with ISO "+ c.getIso() + " and name " + c.getDescription());
			}
		}
	}
	
	
	
	
	public Country getCountry(final String iso, final String name) {
		BeanFactoryLocator bfl = SingletonBeanFactoryLocator.getInstance();
		BeanFactoryReference bf = bfl.useBeanFactory("beanRefFactory");
		CountryManageableDao dao = (CountryManageableDao) bf.getFactory().getBean("CountryManageableDao");
		List list = dao.read(iso, null, null, null, null);
		if (!list.isEmpty()) {
			Country c =(Country) list.iterator().next(); 
			logger.warn("found country with ISO "+c.getIso() + " and id "+c.getId());
			return c;			
		} else {
			java.lang.Long[] em = {};
			Country c = dao.create(iso, name, "", null, em);
			logger.warn("created country with ISO "+c.getIso() + " and id "+c.getId());
			return c;
		}
		
		/*
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
		*/
	}
	
	

	public void mainTest() throws ServiceException {
		logger.info(" ===================== Run Spring Test =====================");
		
		BeanFactoryLocator bfl = SingletonBeanFactoryLocator.getInstance();
		BeanFactoryReference bf = bfl.useBeanFactory("beanRefFactory");
		//PhoneFormatDao phone = (PhoneFormatDao) bf.getFactory().getBean("phoneFormatDao");
		//phone.create("*");

		listAllCountries();
		
		Country de = getCountry("DE", "Germany");
		Country us = getCountry("US", "United States");
		Country uk = getCountry("UK", "United Kingdom");
		Country at = getCountry("AT", "Austria");

		listAllCountries();
		
		
		if (de == null) 	logger.error("Error with country de");
		if (us == null) 	logger.error("Error with country us");
		if (uk == null) 	logger.error("Error with country uk");
		if (at == null) 	logger.error("Error with country at");
	
	}

}
