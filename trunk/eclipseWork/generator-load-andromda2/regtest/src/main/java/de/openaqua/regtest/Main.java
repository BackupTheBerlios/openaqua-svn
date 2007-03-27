package de.openaqua.regtest;

/*
 * @todo: In beanRefFactory.xml: Verweis auf remote irgendwas
 * 
 */

import org.apache.log4j.ConsoleAppender;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.apache.log4j.PatternLayout;

import de.openaqua.dev.exception.ServiceException;


public class Main {
	private static Logger logger = Logger.getRootLogger();


	public static void main(String[] args) throws ServiceException  {
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
	
	public static void testSpring() throws ServiceException {
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
	}

}


