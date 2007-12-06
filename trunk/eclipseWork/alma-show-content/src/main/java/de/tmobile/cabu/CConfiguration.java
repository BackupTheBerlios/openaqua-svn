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

	private TTConnection connection;

	private CConfiguration() {
		super();
	}

	/**
	 * @return the connection
	 */
	final public TTConnection getConnection() {
		return connection;
	}

	/**
	 * @return the error
	 */
	final public boolean isError() {
		if (connection == null) { return true; }
		return !connection.isConnected();
	}

	/**
	 * @param connection
	 *           the connection to set
	 */
	public void setConnection(final TTConnection connection) {
		this.connection = connection;
	}

}
