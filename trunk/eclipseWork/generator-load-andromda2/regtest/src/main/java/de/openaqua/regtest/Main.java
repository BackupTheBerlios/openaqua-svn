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

		//new SpringTest("SpringTest").RunTest();
		//new HibernateTest().RunTest();
		if (new AlmaTest("AlmaTest").RunTest() != true) {
			logger.error("Test not successfull");
		}
		
		
		logger.info("=======================================================");
		logger.info("================Test successfull=======================");
	}
}
