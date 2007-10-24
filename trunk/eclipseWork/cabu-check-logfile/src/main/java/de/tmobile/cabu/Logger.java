/**
 * 
 */
package de.tmobile.cabu;

/**
 * @author behrenan
 * 
 */
public final class Logger {

	private static Logger	INSTANCE	= new Logger();


	static public Logger getRootLogger() {
		return INSTANCE;
	}


	private Logger() {
		super();
	}


	public void debug(final String text) {
		System.err.println("DBG " + text);
	}


	public void empty() {
		out("");
	}


	public void error(final String text) {
		System.err.println("ERR " + text);
	}


	public void header() {
		out("============================================================");
	}


	public void info(final String text) {
		System.err.println("INF " + text);
	}


	public void out(final String text) {
		System.out.println(text);
	}


	public void printHeader() {
		header();
		empty();
		out("The Cabu Logfile checker made a analyses of a CABU logfile");
		out("These are the results:");
		empty();

	}


	public void smallHeader() {
		out("------------------------------------------------------------");
	}


	public void warn(final String text) {
		System.err.println("WRN " + text);
	}

}
