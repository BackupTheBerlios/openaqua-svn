/**
 * 
 */
package de.tmobile.cabu;

/**
 * @author behrenan
 *
 */
final public class Configuration {
	/**
	 * Its a singleton
	 */
	final private static Configuration INSTANCE = new Configuration();
	final private int statMilliSeconds;


	private Configuration() {
		super();
		
		//stat stuff
		statMilliSeconds = 10000;

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
	

}
