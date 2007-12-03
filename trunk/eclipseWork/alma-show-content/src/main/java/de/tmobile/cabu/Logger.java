/**
 * 
 */
package de.tmobile.cabu;

/**
 * @author behrenan
 * 
 */
public class Logger {

	private static Logger INSTANCE = new Logger();

	static public Logger getRootLogger() {
		return INSTANCE;
	}

	private Logger() {
		super();
	}

	public void debug(final String text) {
		System.out.println("DBG " + text);
	}

	public void emptyLine() {
		System.out.println("");
	}

	public void error(final String text) {
		System.out.println("ERR " + text);
	}

	public void info(final String text) {
		System.out.println("INF " + text);
	}

	public void out(final String text) {
		System.out.println(text);
	}

	public void warn(final String text) {
		System.out.println("WRN " + text);
	}
}
