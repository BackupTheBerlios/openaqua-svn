/**
 * 
 */
package de.tmobile.cabu;

import org.apache.log4j.Logger;

/**
 * @author behrenan
 *
 */
public class AlmaConnection {
	private String dsn;
	//private String myDNS;
	//private String myDriver;
	private Logger logger = Logger.getRootLogger();
	private TTConnection connection = null;
	AlmaConnection (String dsn) throws ClassNotFoundException {
		logger.info("Make Connection to: "+dsn);
		this.dsn=dsn;
		
		//myDNS ="jdbc:timesten:direct:PerfTest";
		//myDriver = "com.timesten.jdbc.TimesTenDriver";
		connection = new TTConnection();
		
		
	}

	/**
	 * @return the dsn
	 */
	protected String getDsn() {
		return this.dsn;
	}

	/**
	 * @param dsn the dsn to set
	 */
	protected void setDsn(String dsn) {
		this.dsn = dsn;
	}

	public void listTemplates() {
		logger.info("All known Templates: .................");
		
	}
}
