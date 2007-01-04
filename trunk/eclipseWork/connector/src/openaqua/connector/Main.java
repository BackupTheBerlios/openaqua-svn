/**
 * 
 */
package openaqua.connector;

import org.apache.log4j.ConsoleAppender;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.apache.log4j.PatternLayout;

/**
 * @author tukaram
 *
 */
public class Main {
	private static Logger logger = Logger.getRootLogger();
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			//Setup a Simple Logger
			PatternLayout layout = new PatternLayout( "%-5p [%t] %C{1} -> %m%n" );
	        ConsoleAppender consoleAppender = new ConsoleAppender( layout );
	        logger.addAppender( consoleAppender );
	        logger.setLevel( Level.ALL);

	        //execute the main object
	        Connector c = new Connector();
	        c.start();
	        logger.info("Done");
	        
		} catch( Exception ex ) {
			ex.printStackTrace();
			System.out.println( ex );
	    }

	}

}
