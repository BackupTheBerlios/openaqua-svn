package de.openaqua.regtest;

/*
 * @todo: In beanRefFactory.xml: Verweis auf remote irgendwas
 * 
 */

import org.apache.log4j.ConsoleAppender;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.apache.log4j.PatternLayout;


public class Main {
	private static Logger logger = Logger.getRootLogger();


	public static void main(String[] args)  {
		PatternLayout layout = new PatternLayout( "%-5p [%t] %C{1} -> %m%n" );
		ConsoleAppender consoleAppender = new ConsoleAppender( layout );
		logger.addAppender( consoleAppender );
		logger.setLevel( Level.INFO);
		logger.info("-------------------Begin Test-----------------------");

		//logger.info("-------------------setup Hibernate-----------------------");
		//testHibernate();
		
		testSpring();

	}

	public static void testHibernate() {
		HibernateTest test = new HibernateTest();
		test.mainTest();
		
	}
	
	public static void testSpring() {
		SpringTest test = new SpringTest();
		test.mainTest();
		
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


