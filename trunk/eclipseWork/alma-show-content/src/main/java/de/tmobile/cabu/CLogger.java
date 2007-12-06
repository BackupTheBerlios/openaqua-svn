/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class CLogger {

	private static CLogger INSTANCE = new CLogger();

	static public CLogger getRootLogger() {
		return INSTANCE;
	}

	private CLogger() {
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
