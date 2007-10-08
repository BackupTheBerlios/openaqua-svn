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
	final private int maxConnections;
	final private int maxContracts;
	final private int maxSubsriptions;
	final private int maxInstances;
	final private int reqLoops;
	final private String myDNS; 
	final private String myDriver;
	final private int statMilliSeconds;
	final private boolean useOracle;
	final private boolean doBlopTest;


	private Configuration() {
		super();
		useOracle = true;
		doBlopTest = true;
		maxConnections = 2;
		
		maxContracts = 5000000;
		maxSubsriptions = maxContracts/5;
		maxInstances=maxSubsriptions*3;

		reqLoops     = 10000;
		
		//Timesten
		if (useOracle == false) {
			myDNS ="jdbc:timesten:direct:PerfTest";
			myDriver = "com.timesten.jdbc.TimesTenDriver";
		} else {
			//Oracle
			myDNS ="jdbc:oracle:thin:@ds63801a.mspr.detemobil.de:1521:talmgr"; //TCP
			//myDNS ="jdbc:oracle:oci8:@talmgr.mspr.detemobil.de"; //Thick driver, might be over IPC
			myDriver = "oracle.jdbc.driver.OracleDriver";
		}

		
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
	 * @return the maxInstances
	 */
	public int getMaxInstances() {
		return maxInstances;
	}


	/**
	 * @return the maxSubsriptions
	 */
	public int getMaxSubsriptions() {
		return maxSubsriptions;
	}


	/**
	 * @return the maxContracts
	 */
	public int getMaxContracts() {
		return maxContracts;
	}

	/**
	

	/**
	 * @return the useOracle
	 */
	public final boolean isUseOracle() {
		return useOracle;
	}

	/**
	 * @return the doBlopTest
	 */
	public final boolean isDoBlopTest() {
		return doBlopTest;
	}


}
