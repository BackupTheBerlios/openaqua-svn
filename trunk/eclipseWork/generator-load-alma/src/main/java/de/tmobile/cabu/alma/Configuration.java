/**
 *
 */
package de.tmobile.cabu.alma;

/**
 * @author behrenan
 *
 */
final public class Configuration {
	final private static Configuration INSTANCE = new Configuration();
	final private int maxConnections;
	final private int reqLoops;
	final private int statMilliSeconds;
	final private int almaPort;
	final private String almaHost;


	private Configuration() {
		super();
		maxConnections = 1;
		reqLoops     = 100000;
		statMilliSeconds = 10000;
		almaPort = 32504;
		almaHost = "localhost";

	}

	/*
	 * @result returns a object reference to this singleton
	 */
	final public static Configuration getInstance() {
		return INSTANCE;
	}

	public int getStatsAllMilliseconds() {
		return statMilliSeconds;
	}

	public int getReqLoops() {
		return reqLoops;
	}

	/**
	 * @return the threadCounter
	 */
	public int getMaxConnections() {
		return maxConnections;
	}

	/**
	 * @return the almaHost
	 */
	public String getAlmaHost() {
		return almaHost;
	}


	/**
	 * @return the almaPort
	 */
	public int getAlmaPort() {
		return almaPort;
	}


}
