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
	final private String myDNS; 
	final private String myDriver;
	final private int statMilliSeconds;


	private Configuration() {
		super();
		
		
		//Timesten
		myDNS ="jdbc:timesten:direct:PerfTest";
		myDriver = "com.timesten.jdbc.TimesTenDriver";


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
	
	public String getDriver() {
		return myDriver;
	}
	
	public String getDNS() {
		return myDNS;
	}


}
