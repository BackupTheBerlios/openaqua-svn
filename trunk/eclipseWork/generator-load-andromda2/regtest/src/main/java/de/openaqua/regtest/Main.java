package de.openaqua.regtest;

/*
 * @todo: In beanRefFactory.xml: Verweis auf remote irgendwas
 * 
 */

import org.apache.log4j.ConsoleAppender;

import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.apache.log4j.PatternLayout;
import org.springframework.beans.factory.access.BeanFactoryLocator;
import org.springframework.beans.factory.access.BeanFactoryReference;
import org.springframework.beans.factory.access.SingletonBeanFactoryLocator;
import org.springframework.beans.factory.xml.XmlBeanFactory;
import org.springframework.core.io.ClassPathResource;

import de.openaqua.dev.entities.Country;
import de.openaqua.dev.entities.CountryDao;
import de.openaqua.dev.entities.CountryDaoImpl;
import de.openaqua.dev.exception.ServiceException;
import de.openaqua.dev.services.CountryService;
import de.openaqua.dev.vo.CountryVO;


public class Main {
	private static Logger logger = Logger.getRootLogger();

	public static void main(String[] args) throws ServiceException {
		PatternLayout layout = new PatternLayout( "%-5p [%t] %C{1} -> %m%n" );
		ConsoleAppender consoleAppender = new ConsoleAppender( layout );
		logger.addAppender( consoleAppender );
		logger.setLevel( Level.ALL);
		logger.info("-------------------Begin Test-----------------------");
		playWithCountry();
		playWithCountryByDb();
		hibernateTest();
		springTest();

	}

	public static void playWithCountry() {
		logger.info("-------------------playWithCountry()-----------------------");
		Country c =  Country.Factory.newInstance();
		CountryDumper dumper = new CountryDumper();
		dumper.dumpCountry(c);		
	}

	public static void playWithCountryByDb() {
		logger.info("-------------------playWithCountryByDb()-----------------------");
		//CountryDao dao = new CountryDaoImpl();
		//CountryDumper dumper = new CountryDumper();

		//Country c = dao.create("Germany", "+49");
		//c.setIso("DE");

		//dumper.dumpCountry(c);		
	}

	public static void hibernateTest()  {
		logger.info("-------------------play with hibernateTest()-----------------------");
		
		
	}

	public static void springTest() throws ServiceException {
		logger.info("-------------------play with springTest()-----------------------");
		String segs[] = System.getProperty("java.class.path",".").split( ":" );
		for (int i = 0; i < segs.length; ++i) {
			logger.info("Path: " + segs[i]);		
		}
		
		BeanFactoryLocator bfl = SingletonBeanFactoryLocator.getInstance();
		 BeanFactoryReference bf = bfl.useBeanFactory("beanRefFactory");
		 CountryService cs = (CountryService) bf.getFactory().getBean("countryService");
		 CountryVO c = cs.getCountryByIso("DE");
		 if (c != null) {
			 logger.info("Got CountryVO for DE:");
			 logger.info("id="+c.getId());
		 } else {
			 logger.info("Got not CountryVO for DE:");
			 CountryVO d = new CountryVO();
			 d.setIso("DE");
			 d.setDescription("Germany");
			 d.setPhoneFormat("");
			 d.setPredial("+49");
			 //CountryDao dao = new CountryDaoImpl();
			 //dao.create(description, preDial)
		 }
		
		//ClassPathResource res = new ClassPathResource("applicationContext.xml");
		 // XmlBeanFactory factory = new XmlBeanFactory(res);
		 //CountryService myService = (CountryService) factory.getBean("countryService");
		 //CountryVO[] list =  myService.getAllCountries();
		
		//PizzaOrderService myService = (PizzaOrderService) factory.getBean("pizzaOrderService");
	}

}


