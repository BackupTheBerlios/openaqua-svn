/**
 *
 */
package de.openaqua.regTestHelper;

/**
 * @author behrenan
 *
 */
final public class Configuration {
	final private static Configuration INSTANCE = new Configuration();
	final private int maxConnections;
	final private int reqLoops;
	final private int statMilliSeconds;


	private Configuration() {
		super();
		maxConnections = 2;
		reqLoops     = 100;
		statMilliSeconds = 1000;

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

}