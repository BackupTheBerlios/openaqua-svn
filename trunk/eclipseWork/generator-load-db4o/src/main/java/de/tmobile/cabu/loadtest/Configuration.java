/**
 *
 */
package de.tmobile.cabu.loadtest;


/**
 * @author behrenan
 *
 */
final public class Configuration {
	/**
	 * Its a singleton
	 */
	final private static Configuration Instance = new Configuration();
	final private int maxConnections;
	final private int maxContracts;
	final private int maxSubsriptions;
	final private int maxInstances;
	final private int reqLoops;
	final private String myDNS;
	final private String myDriver;
	final private int statMilliSeconds;
	final private boolean setupDatabase;


	private Configuration() {
		super();
		maxConnections = 2;

		maxContracts = 20000;
		maxSubsriptions = maxContracts/5;
		maxInstances=maxSubsriptions*3;

		reqLoops     = 1000;
		myDNS ="jdbc:timesten:direct:PerfTest";
		myDriver = "com.timesten.jdbc.TimesTenDriver";
		statMilliSeconds = 1000;
		
		setupDatabase = true;

	}


	/**
	 * @return the instance
	 */
	public static final Configuration getInstance() {
		return Instance;
	}


	/**
	 * @return the maxConnections
	 */
	public final int getMaxConnections() {
		return maxConnections;
	}


	/**
	 * @return the maxContracts
	 */
	public final int getMaxContracts() {
		return maxContracts;
	}


	/**
	 * @return the maxInstances
	 */
	public final int getMaxInstances() {
		return maxInstances;
	}


	/**
	 * @return the maxSubsriptions
	 */
	public final int getMaxSubsriptions() {
		return maxSubsriptions;
	}


	/**
	 * @return the myDNS
	 */
	public final String getMyDNS() {
		return myDNS;
	}


	/**
	 * @return the myDriver
	 */
	public final String getMyDriver() {
		return myDriver;
	}


	/**
	 * @return the reqLoops
	 */
	public final int getReqLoops() {
		return reqLoops;
	}


	/**
	 * @return the setupDatabase
	 */
	public final boolean isSetupDatabase() {
		return setupDatabase;
	}


	/**
	 * @return the statMilliSeconds
	 */
	public final int getStatMilliSeconds() {
		return statMilliSeconds;
	}

}
