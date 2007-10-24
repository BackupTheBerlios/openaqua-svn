/**
 * 
 */
package de.tmobile.cabu;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.TimeZone;

/**
 * @author behrenan
 *
 */
final public class Configuration {
	private static Configuration INSTANCE = new Configuration();
	private String logFile;
	private DateFormat format;
	
	private Configuration() {
		super();
		logFile=null;
		format = new SimpleDateFormat( "yyyyMMdd HHmmss" );
		format.setTimeZone(TimeZone.getTimeZone("UTC"));

	}
	
	static public Configuration getInstance() {
		return INSTANCE;
	}
	

	public String getLogFile() {
		return this.logFile;
	}

	public void setLogFile(final String logFile) {
		this.logFile = logFile;
	}

	public DateFormat getDateFormat() {
		return format;
	}
}
