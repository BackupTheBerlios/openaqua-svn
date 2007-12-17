/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
final public class CLogger {

	final private static CLogger INSTANCE = new CLogger();

	final static public CLogger getRootLogger() {
		return INSTANCE;
	}

	private CLogger() {
		super();
	}

	final public void debug(final String text) {
		System.out.println("DBG " + text);
	}

	final public void emptyLine() {
		System.out.println("");
	}

	final public void error(final String text) {
		System.out.println("ERR " + text);
	}

	final public void info(final String text) {
		System.out.println("INF " + text);
	}

	final public void out(final String text) {
		System.out.println(text);
	}

	final public void warn(final String text) {
		System.out.println("WRN " + text);
	}
}
