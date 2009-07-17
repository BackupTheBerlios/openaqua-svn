/**
 * 
 */
package de.tmobile.cabu;




/**
 * @author behrenan
 * 
 */
final public class CConfiguration {
	final private static CConfiguration INSTANCE = new CConfiguration();

	/*
	 * @result returns a object reference to this singleton
	 */
	final public static CConfiguration getInstance() {
		return INSTANCE;
	}

	private String connectionDriver;
	private String connectionDsn;

	private CConfiguration() {
		super();
	}


	/**
	 * @return the connectionDriver
	 */
	public String getConnectionDriver() {
		return connectionDriver;
	}

	/**
	 * @return the connectionDsn
	 */
	public String getConnectionDsn() {
		return connectionDsn;
	}

	/**
	 * @param connectionDriver
	 *           the connectionDriver to set
	 */
	public void setConnectionDriver(final String connectionDriver) {
		this.connectionDriver = connectionDriver;
	}

	/**
	 * @param connectionDsn
	 *           the connectionDsn to set
	 */
	public void setConnectionDsn(final String connectionDsn) {
		this.connectionDsn = connectionDsn;
	}
}
