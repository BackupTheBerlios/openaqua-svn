package de.openaqua.regtest;

import org.apache.log4j.ConsoleAppender;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.apache.log4j.PatternLayout;

import de.openaqua.dev.entities.Country;
import de.openaqua.dev.entities.CountryDao;
import de.openaqua.dev.entities.CountryDaoImpl;

public class Main {
	private static Logger logger = Logger.getRootLogger();

	public static void main(String[] args) {
		PatternLayout layout = new PatternLayout( "%-5p [%t] %C{1} -> %m%n" );
	    ConsoleAppender consoleAppender = new ConsoleAppender( layout );
	    logger.addAppender( consoleAppender );
	    logger.setLevel( Level.ALL);
	    logger.info("-------------------Begin Test-----------------------");
	    playWithCountry();
	    playWithCountryByDb();

	}
	
	public static void playWithCountry() {
		logger.info("-------------------playWithCountry()-----------------------");
		Country c =  Country.Factory.newInstance();
		CountryDumper dumper = new CountryDumper();
		dumper.dumpCountry(c);		
	}

	public static void playWithCountryByDb() {
		logger.info("-------------------playWithCountryByDb()-----------------------");
		CountryDao dao = new CountryDaoImpl();
		CountryDumper dumper = new CountryDumper();
		
		Country c = dao.create("Germany", "+49");
		c.setIso("DE");
		
		dumper.dumpCountry(c);		
	}
}
