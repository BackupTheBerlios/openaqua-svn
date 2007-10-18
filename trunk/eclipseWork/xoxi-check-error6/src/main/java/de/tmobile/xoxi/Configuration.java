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
	private String logDir;
	private String mailToFile;
	private boolean sendMail;
	
	static public Configuration getInstance() {
		return INSTANCE;
	}
	
	private Configuration() {
		logDir=null;
		mailToFile=null;
		sendMail=false;
		
	}

	public String getLogDir() {
		return this.logDir;
	}

	public void setLogDir(String logDir) {
		this.logDir = logDir;
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
