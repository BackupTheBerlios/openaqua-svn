/**
 * 
 */
package de.tmobile.cabu;

/**
 * @author behrenan
 * 
 */
public class Main {

	final private static Logger	logger	= Logger.getRootLogger();


	/**
	 * @param args
	 */
	public static void main(final String[] args) {
		final Application app = new Application();
		int returncode;
		try {
			returncode = app.run(args);
		} catch (final Exception e) {
			// e.printStackTrace();
			logger.error("Could not found file");
			returncode = -10;
		}
		System.exit(returncode);
	}

}
