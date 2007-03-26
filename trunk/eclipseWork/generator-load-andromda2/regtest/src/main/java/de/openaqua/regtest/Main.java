package de.openaqua.regtest;

/*
 * @todo: In beanRefFactory.xml: Verweis auf remote irgendwas
 * 
 */

import org.apache.log4j.ConsoleAppender;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.apache.log4j.PatternLayout;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.classic.Session;
import org.springframework.beans.factory.access.BeanFactoryLocator;
import org.springframework.beans.factory.access.BeanFactoryReference;
import org.springframework.beans.factory.access.SingletonBeanFactoryLocator;
import de.openaqua.dev.entities.Country;
import de.openaqua.dev.entities.CountryImpl;
import de.openaqua.dev.entities.PhoneFormat;
import de.openaqua.dev.entities.PhoneFormatImpl;
import de.openaqua.dev.services.CountryService;



public class Main {
	private static Logger logger = Logger.getRootLogger();


	public static void main(String[] args)  {
		PatternLayout layout = new PatternLayout( "%-5p [%t] %C{1} -> %m%n" );
		ConsoleAppender consoleAppender = new ConsoleAppender( layout );
		logger.addAppender( consoleAppender );
		logger.setLevel( Level.ALL);
		logger.info("-------------------Begin Test-----------------------");

		logger.info("-------------------setup Hibernate-----------------------");
		testHibernate();
		//playWithCountry();
		//playWithCountryByDb();
		//hibernateTest();
		//springTest();

	}

	public static void testHibernate() {
		SessionFactory sessionFactory = new org.hibernate.cfg.Configuration().configure("hibernate.cfg.mapping.xml").buildSessionFactory();
		Session session = sessionFactory.openSession();
		Transaction trx = session.beginTransaction();
		
		PhoneFormat p = new PhoneFormatImpl();
		p.setFormat(".*\\-.*");
		session.save(p);
		long id = p.getId();
		if ( p.getId() != id) {
			logger.info("ID was: " + id + " is: "+ p.getId());
		} else {
			logger.info("PhoneFormat stored id is " + p.getId());
		}
		
		Country c = new CountryImpl();
		c.setIso("DE");
		c.setDescription("Germany");
		c.setPreDial("+49");
		c.getPhoneFormat().add(p);
		session.save(c);
		long cId = c.getId();
		if ( c.getId() != cId ) {
			logger.info("iso was: " + cId + " is: "+ c.getId() );
		}
		logger.info("Country c stored");
		
		trx.commit();
		
	}
	
	public static void playWithCountry() {
		logger.info("-------------------playWithCountry()-----------------------");
		/*
		Country c =  Country.Factory.newInstance();
		CountryDumper dumper = new CountryDumper();
		dumper.dumpCountry(c);
		*/		
	}

	public static void playWithCountryByDb() {
		logger.info("-------------------playWithCountryByDb()-----------------------");
		//CountryDao dao = new CountryDaoImpl();
		//CountryDumper dumper = new CountryDumper();

		//Country c = dao.create("Germany", "+49");
		//c.setIso("DE");

		//dumper.dumpCountry(c);		
	}


	public static void springTest()  {
		logger.info("-------------------play with springTest()-----------------------");
		String segs[] = System.getProperty("java.class.path",".").split( ":" );
		for (int i = 0; i < segs.length; ++i) {
			logger.info("Path: " + segs[i]);		
		}
		
		//BeanFactoryLocator bfl = SingletonBeanFactoryLocator.getInstance();
		//		 BeanFactoryReference bf = bfl.useBeanFactory("beanRefFactory");
//		 CountryService cs = (CountryService) bf.getFactory().getBean("countryService");
			/*
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
		 */
		
		//ClassPathResource res = new ClassPathResource("applicationContext.xml");
		 // XmlBeanFactory factory = new XmlBeanFactory(res);
		 //CountryService myService = (CountryService) factory.getBean("countryService");
		 //CountryVO[] list =  myService.getAllCountries();
		
		//PizzaOrderService myService = (PizzaOrderService) factory.getBean("pizzaOrderService");
	}

}


