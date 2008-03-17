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

	/*
	 * @result returns a object reference to this singleton
	 */
	final public static Configuration getInstance() {
		return INSTANCE;
	}
	final private int maxConnections;
	final private int reqLoops;
	final private int statMilliSeconds;
	private int almaPort;
	private String almaHost;
	private int sleep;

	private Configuration() {
		super();
		maxConnections = 5;
		reqLoops = 100000;
		statMilliSeconds = 10000;
		almaPort = 0;
		sleep = 1000;
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

	/**
	 * @return the threadCounter
	 */
	public int getMaxConnections() {
		return maxConnections;
	}

	public int getReqLoops() {
		return reqLoops;
	}

	public int getSleepTime() {
		return sleep;
	}

	public int getStatsAllMilliseconds() {
		return statMilliSeconds;
	}

	public void setAlmaHost(final String host) {
		almaHost = host;
	}

	public void setAlmaPort(final int port) {
		almaPort = port;
	}

	public void setSleepTime(final int sleep) {
		this.sleep = sleep;
	}
}
