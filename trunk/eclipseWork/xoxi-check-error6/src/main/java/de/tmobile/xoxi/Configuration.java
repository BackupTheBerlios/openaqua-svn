/**
 * 
 */
package de.tmobile.xoxi;

/**
 * @author behrenan
 *
 */
final public class Configuration {
	private static Configuration INSTANCE = new Configuration();
	private String logFile;
	
	static public Configuration getInstance() {
		return INSTANCE;
	}
	
	private Configuration() {
		logFile=null;
	}

	public String getLogFile() {
		return this.logFile;
	}

	public void setLogFile(final String logFile) {
		this.logFile = logFile;
	}

}
