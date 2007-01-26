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
	private int maxConnections;
	private int maxContracts;
	private int maxSubsriptions;
	private int maxInstances;
	private int reqLoops;
	private String myDNS; 
	private String myDriver;
	private int statMilliSeconds;


	private Configuration() {
		super();
		maxConnections = 10;
		
		maxContracts = 500000;
		maxSubsriptions = maxContracts/5;
		maxInstances=maxSubsriptions*3;

		reqLoops     = 10000;
		myDNS ="jdbc:timesten:direct:PerfTest";
		myDriver = "com.timesten.jdbc.TimesTenDriver";
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
	
	public String getDriver() {
		return myDriver;
	}
	
	public String getDNS() {
		return myDNS;
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
	 */
	public void setMaxConnections(int maxConnections) {
		this.maxConnections = maxConnections;	

	}

	/**
	 * @return the maxInstances
	 */
	public int getMaxInstances() {
		return maxInstances;
	}

	/**
	 * @param maxInstances the maxInstances to set
	 */
	public void setMaxInstances(int maxInstances) {
		this.maxInstances = maxInstances;
	}

	/**
	 * @return the maxSubsriptions
	 */
	public int getMaxSubsriptions() {
		return maxSubsriptions;
	}

	/**
	 * @param maxSubsriptions the maxSubsriptions to set
	 */
	public void setMaxSubsriptions(int maxSubsriptions) {
		this.maxSubsriptions = maxSubsriptions;
	}

	/**
	 * @return the maxContracts
	 */
	public int getMaxContracts() {
		return maxContracts;
	}

	/**
	 * @param maxContracts the maxContracts to set
	 */
	public void setMaxContracts(int maxContracts) {
		this.maxContracts = maxContracts;
	}


}
