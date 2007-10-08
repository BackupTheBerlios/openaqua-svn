/**
 * 
 */
package de.tmobile.cabu;

import org.apache.log4j.ConsoleAppender;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.apache.log4j.SimpleLayout;

/**
 * @author behrenan
 * 
 */
public class Main {
	static TTConnection mainConnection = null;

	final private static Logger logger = Logger.getRootLogger();

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		setupLogging();

		AlmaConnection alma;
		try {
			alma = new AlmaConnection("DSN");
		} catch (ClassNotFoundException e) {
			logger.error("Class not Found");
			e.printStackTrace();
			return;
		}
		alma.listTemplates();

	}

	private static void setupLogging() {
		SimpleLayout layout = new SimpleLayout();
		ConsoleAppender consoleAppender = new ConsoleAppender(layout);
		logger.addAppender(consoleAppender);
		// ALL | DEBUG | INFO | WARN | ERROR | FATAL | OFF:
		logger.setLevel(Level.ALL);
		logger.debug("Logger Environment set up");
	}

}
