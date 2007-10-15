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
	private Logger() {super();}
	
	
	static public Logger getRootLogger() {
		return INSTANCE;
	}
	
	public void debug(final String text) {
		System.out.println("DBG " + text);
	}
	public void info(final String text) {
		System.out.println("INF " + text);
	}
	public void error(final String text) {
		System.out.println("ERR " + text);
	}
	public void warn(final String text) {
		System.out.println("WRN " + text);
	}
}
