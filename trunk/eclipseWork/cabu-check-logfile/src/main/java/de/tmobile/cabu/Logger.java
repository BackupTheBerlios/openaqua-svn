/**
 * 
 */
package de.tmobile.cabu;



/**
 * @author behrenan
 * 
 */
public final class Logger {

	private static Logger INSTANCE = new Logger();


	private Logger() {
		super();
	}
	
	static public Logger getRootLogger() {
		return INSTANCE;
	}


	public void header()  {
		out("============================================================");
	}

	public void smallHeader()  {
		out("------------------------------------------------------------");
	}

	public void empty()  {
		out("");
	}

	public void debug(final String text) {
		System.err.println("DBG " + text);
	}

	public void info(final String text) {
		System.err.println("INF " + text);
	}

	public void error(final String text) {
		System.err.println("ERR " + text);
	}

	public void warn(final String text) {
		System.err.println("WRN " + text);
	}

	public void out(final String text)  {
		System.out.println(text);
	}

	public void printHeader() {
		header();
		empty();
		out ("The Cabu Logfile checker made a analyses of a CABU logfile");
		out ("These are the result:");
		empty();

	}
	
}
