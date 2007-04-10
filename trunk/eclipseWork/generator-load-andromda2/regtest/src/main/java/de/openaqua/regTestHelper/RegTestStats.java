/**
 *
 */
package de.openaqua.regTestHelper;


import java.util.Locale;
import java.util.concurrent.locks.ReentrantLock;



/**
 * Collects statistical information
 *
 */
final public class RegTestStats {
	final private static RegTestStats INSTANCE = new RegTestStats(); //yepp, is a singleton
	private int  counterRead;
	private int  counterWrite;
	private long globalTime;
	private ReentrantLock lockWrite = new ReentrantLock();
	private ReentrantLock lockRead = new ReentrantLock();


	/*
	 * Constructor
	 */
	private RegTestStats() {
		counterRead = 0;
		globalTime = 0L;
	}

	/*
	 * @result returns a object reference to this singleton
	 */
	final public static RegTestStats getInstance() {
		return INSTANCE;
	}


	public void addReadResults(int pCounter) {
		lockRead.lock();
		try {
			this.counterRead += pCounter;
		} finally {
			lockRead.unlock();
		}
		return;
	}

	public void addWriteResults(int pCounter) {
		lockWrite.lock();
		try {
			this.counterWrite += pCounter;
		} finally {
			lockWrite.unlock();
		}
		return;
	}


	/*
	 * Prints the results
	 */

	private void printResultLine (final int cr, final int cw, final int msec) {
		int myCounterRead = 1;
		int myCounterWrite = 1;

		if (cr>0) myCounterRead  = cr;
		if (cw>0) myCounterWrite = cw;

		int sR = msec * 1000  / myCounterRead;
		int sW = msec * 1000  / myCounterWrite;

		if (cr<1) {myCounterRead  = 0; sR=0;}
		if (cw<1) {myCounterWrite = 0; sW=0;}

		System.out.printf(Locale.GERMANY, "In %,d ms:\t%,7d read(%,7dms)\t%,7d write(%,7dms)%n", msec, myCounterRead, sR, myCounterWrite, sW);
	}



	
	
	public void printResults(int msec) {
		int acounterRead = 0;
		int acounterWrite = 0;

		//get write results
		lockWrite.lock();
		try {
			acounterWrite = counterWrite;
			counterWrite = 0;
		} finally {
			lockWrite.unlock();
		}


		//get read results
		lockRead.lock();
		try {
			acounterRead = counterRead;
			counterRead = 0;
		} finally {
			lockRead.unlock();
		}


		//print read stat
		printResultLine(acounterRead, acounterWrite, msec);

		//bye bye
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