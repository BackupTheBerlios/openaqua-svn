/**
 * 
 */
package de.tmobile.xoxi;

import java.io.FileNotFoundException;


/**
 * @author behrenan
 * 
 */
public class Main {

	final private static Logger logger = Logger.getRootLogger();


	/**
	 * @param args
	 */
	public static void main(String[] args) {
		logger.info("Start Application");
		Application app = new Application();
		int returncode;
			try {
				returncode = app.run(args);
			} catch (FileNotFoundException e) {
				//e.printStackTrace();
				logger.error("Could not found file");
				returncode = -10;
			}
			System.exit(returncode);
	}

}
