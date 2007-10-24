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
	private int logFileType = 0;
	private boolean showAll = false;
	
	private Configuration() {
		super();
		logFile=null;
		format = new SimpleDateFormat( "yyyyMMddHHmmss" );
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

	
	/*
	 * 0 - unknown
	 * 1 - CHC
	 * 2 - XOXI
	 * 
	 */
	public int getLogFileType() {
		return this.logFileType;
	}

	public void setLogFileType(int logFileType) {
		this.logFileType = logFileType;
	}

	/**
	 * @return the showAll
	 */
	public boolean isShowAll() {
		return this.showAll;
	}

	/**
	 * @param showAll the showAll to set
	 */
	public void setShowAll(boolean showAll) {
		this.showAll = showAll;
	}
}
