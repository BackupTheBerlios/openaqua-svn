package de.openaqua.regtest;

import org.apache.log4j.ConsoleAppender;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.apache.log4j.PatternLayout;

import de.openaqua.dev.entities.Country;

public class Main {
	//private static Logger logger = Logger.getRootLogger();
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		/*
		PatternLayout layout = new PatternLayout( "%-5p [%t] %C{1} -> %m%n" );
	    ConsoleAppender consoleAppender = new ConsoleAppender( layout );
	    logger.addAppender( consoleAppender );
	    logger.setLevel( Level.ALL);
*/
		Country c = new Country.Factory().newInstance();
		c.getIso();

	}

}
