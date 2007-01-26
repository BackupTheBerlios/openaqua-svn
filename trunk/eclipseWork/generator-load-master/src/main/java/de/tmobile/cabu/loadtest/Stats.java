/**
 *
 */
package de.tmobile.cabu.loadtest;

import java.util.concurrent.locks.ReentrantReadWriteLock;

/**
 * Collects statistical information
 *
 */
final public class Stats {
	final private static Stats INSTANCE = new Stats(); //yepp, is a singleton
	private ReentrantReadWriteLock lockW = new ReentrantReadWriteLock(true);//the class lock
	private ReentrantReadWriteLock lockR = new ReentrantReadWriteLock(true);//the class lock
	private ReentrantReadWriteLock lockG = new ReentrantReadWriteLock(true);//the class lock
	private int  counterWrite;
	private int  counterRead;
	private long globalTime;


	/*
	 * Constructor
	 */
	private Stats() {
		counterWrite = 0;
		counterRead = 0;
		globalTime = 0L;
	}

	/*
	 * @result returns a object reference to this singleton
	 */
	final public static Stats getInstance() {
		return INSTANCE;
	}


	public void addReadResults(int pCounter) {
		lockR.writeLock().lock();
		try {
			this.counterRead += pCounter;
		} finally {
			lockR.writeLock().unlock();
		}
		return;
	}


	public void addWriteResults(int pCounter) {
		lockW.writeLock().lock();
		try {
			this.counterWrite += pCounter;
		} finally {
			lockW.writeLock().unlock();
		}
		return;
	}


	/*
	 * resets all stored values
	 */
	public void resetResults() {
		lockW.writeLock().lock();
		lockR.writeLock().lock();
		try {
			counterWrite = 0;
			counterRead = 0;
		} finally {
			lockW.writeLock().unlock();
			lockR.writeLock().unlock();
		}
		return;
	}


	/*
	 * Prints the results
	 */
	public void printResults(int msec) {
		int  acounterWrite;
		int  acounterRead;

		lockW.writeLock().lock();
		lockR.writeLock().lock();

		try {
			acounterWrite = counterWrite;
			acounterRead = counterRead;
			if (acounterRead == 0) acounterRead  = 1;
			if (acounterWrite == 0) acounterWrite  = 1;

			counterWrite = 0;
			counterRead = 0;

		} finally {
			lockW.writeLock().unlock();
			lockR.writeLock().unlock();
		}


		//print read Stats
		{
			float s  = msec * 1000 / acounterRead;
			System.out.printf("%s in %s msec:\t%s\t%s\n", "read ", msec, acounterRead, s);
		}
		//print write Stats
		{
			//float s  = msec * 1000 / acounterWrite;
			//System.out.printf("%s in %s msec:\t%s\t%s\n", "write", msec, acounterWrite, s);
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
		lockG.writeLock().lock();
		try {
			this.globalTime = globalTime;
		} finally {
			lockG.writeLock().unlock();
		}
		return;
	}
}
