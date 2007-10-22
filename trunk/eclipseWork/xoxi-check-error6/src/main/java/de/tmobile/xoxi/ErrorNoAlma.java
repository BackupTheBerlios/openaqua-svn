/**
 * 
 */
package de.tmobile.xoxi;

/**
 * @author behrenan
 *
 */
public class ErrorNoAlma {
	private static ErrorNoAlma INSTANCE = new ErrorNoAlma();
	private int count = 0;
	
	public static ErrorNoAlma getInstance() {
		return INSTANCE;
	}

	
	public void add(LogFileLine line) {
		count++;
	}
	
	public void print() {
		Logger log = Logger.getRootLogger();
		log.out("-------------------------------------------------------------");
		log.out("Found "+count+" Errors while Alma was not available");
		log.out("");
		
	}
}
