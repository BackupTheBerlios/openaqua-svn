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
	final public static Configuration INSTANCE = new Configuration();
	private int maxConnections;
	private int maxContracts;
	private int reqLoops;
	
	
	private Configuration() {
		super();
		maxConnections = 100;
		maxContracts = 200;
		reqLoops     = 100;
		
	}
	
	/*
	 * @result returns a object reference to this singleton
	 */
	final public static Configuration getInstance() {
		return INSTANCE;
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
	 */
	public void setMaxConnections(int maxConnections) {
		this.maxConnections = maxConnections;
	}
	

}
