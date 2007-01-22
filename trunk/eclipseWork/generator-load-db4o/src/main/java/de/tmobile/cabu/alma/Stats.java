/**
 * 
 */
package de.tmobile.cabu.alma;


/**
 * Collects statistical information
 *
 */
final public class Stats {
	final private static Stats INSTANCE = new Stats(); //yepp, is a singleton
	private int  counterRead;
	private long globalTime;


	/*
	 * Constructor
	 */
	private Stats() {
		counterRead = 0;
		globalTime = 0L;
	}

	/*
	 * @result returns a object reference to this singleton
	 */
	final public static Stats getInstance() {
		return INSTANCE;
	}


	public synchronized void addReadResults(int pCounter) {
		this.counterRead += pCounter;
		return;
	}



	/*
	 * Prints the results
	 */
	public synchronized void printResults(int msec) {
		int  acounterRead = counterRead;		counterRead = 0;

		if (acounterRead > 0) {
			float s = msec * 1000  / acounterRead;
			System.out.printf("%s in %s msec:\t%s\t%s\n", "read ", msec, acounterRead, s);
		} else {
			System.out.printf("No successfull requests\n");
			
		}


		return;
	}

	/**
	 * @return the globalTime
	 */
	public long getGlobalTime() {
		return globalTime;
	}

	/**
	 * @param globalTime the globalTime to set
	 */
	public void setGlobalTime(long globalTime) {
		this.globalTime = globalTime;
		return;
	}
}
