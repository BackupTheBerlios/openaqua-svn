/**
 * 
 */
package de.tmobile.cabu;

/**
 * @author behrenan
 * 
 */
final public class Configuration {
	final private static Configuration INSTANCE = new Configuration();

	/*
	 * @result returns a object reference to this singleton
	 */
	final public static Configuration getInstance() {
		return INSTANCE;
	}

	final private int statMilliSeconds;
	private TTConnection connection;

	private Configuration() {
		super();
		statMilliSeconds = 10000; // stat stuff
	}

	/**
	 * @return the connection
	 */
	final public TTConnection getConnection() {
		return connection;
	}

	final public int getStatsAllMilliseconds() {
		return statMilliSeconds;
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
