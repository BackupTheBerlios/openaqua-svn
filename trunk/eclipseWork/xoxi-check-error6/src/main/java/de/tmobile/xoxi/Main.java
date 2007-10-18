/**
 * 
 */
package de.tmobile.xoxi;


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
		int returncode = app.run(args);
		System.exit(returncode);
	}

}
