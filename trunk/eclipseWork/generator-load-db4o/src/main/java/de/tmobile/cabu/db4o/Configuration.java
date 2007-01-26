/**
 * 
 */
package de.tmobile.cabu.db4o;

/**
 * @author behrenan
 *
 */
final public class Configuration {
	/**
	 * Its a singleton
	 */
	final private static Configuration INSTANCE = new Configuration();
	final private int maxConnections;
	final private int maxContracts;
	final private int reqLoops;
	final private int statMilliSeconds;
	final private boolean setupDatebase;


	private Configuration() {
		super();
		maxConnections = 2;
		maxContracts = 10000;
		reqLoops     = 200;
		statMilliSeconds = 10000;
		setupDatebase = true;

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

	public int getMaxContracts() {
		return maxContracts;
	}
	/**
	 * @return the threadCounter
	 */
	public int getMaxConnections() {
		return maxConnections;
	}

	/**
	 * @return the setupDatebase
	 */
	public boolean isSetupDatebase() {
		return setupDatebase;
	}
}
