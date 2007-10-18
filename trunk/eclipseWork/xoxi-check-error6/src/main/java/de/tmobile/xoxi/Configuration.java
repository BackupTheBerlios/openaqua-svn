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
	private String mailToFile;
	private boolean sendMail;
	
	static public Configuration getInstance() {
		return INSTANCE;
	}
	
	private Configuration() {
		logFile=null;
		mailToFile=null;
		sendMail=false;
		
	}

	public String getLogFile() {
		return this.logFile;
	}

	public void setLogFile(final String logFile) {
		this.logFile = logFile;
	}

	public String getMailToFile() {
		return this.mailToFile;
	}

	public void setMailToFile(String mailToFile) {
		this.mailToFile = mailToFile;
		if (mailToFile != null) sendMail = true;
	}

	public boolean isSendMail() {
		return this.sendMail;
	}

	public void setSendMail(boolean sendMail) {
		this.sendMail = sendMail;
	}

}
