package de.openaqua.regTestHelper;

/**
 * @author behrenan
 *
 */
final public class RegTestConfiguration {
	final private static RegTestConfiguration INSTANCE = new RegTestConfiguration();
	final private int maxConnections;
	final private int reqLoops;
	final private int statMilliSeconds;


	private RegTestConfiguration() {
		super();
		maxConnections = 8;
		reqLoops     = 1000;
		statMilliSeconds = 2000;

	}

	/*
	 * @result returns a object reference to this singleton
	 */
	final public static RegTestConfiguration getInstance() {
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
