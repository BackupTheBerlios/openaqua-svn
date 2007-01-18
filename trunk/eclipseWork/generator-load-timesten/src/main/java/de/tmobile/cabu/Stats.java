/**
 * 
 */
package de.tmobile.cabu;

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
	private long timeWrite;
	private int  counterRead;
	private long timeRead;
	private long globalTime;


	/*
	 * Constructor
	 */
	private Stats() {
		counterWrite = 0;
		timeWrite = 1L;
		counterRead = 0;
		timeRead = 1L;
		globalTime = 0L;
	}

	/*
	 * @result returns a object reference to this singleton
	 */
	final public static Stats getInstance() {
		return INSTANCE;
	}

	
	public void addReadResults(int pCounter, long pTime) {
		lockR.writeLock().lock();
		try {
			this.counterRead += pCounter;
			this.timeRead += pTime;
		} finally {
			lockR.writeLock().unlock();
		}
		return;
	}

	
	public void addWriteResults(int pCounter, long pTime) {
		lockW.writeLock().lock();
		try {
			this.counterWrite += pCounter;
			this.timeWrite += pTime;
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
			timeWrite = 0L;
			counterRead = 0;
			timeRead = 0L;
		} finally {
			lockW.writeLock().unlock();
			lockR.writeLock().unlock();
		}
		return;
	}
	
	
	/*
	 * Prints the results
	 */
	public void printResults() {
   	int  acounterWrite;
   	long atimeWrite;
   	int  acounterRead;
   	long atimeRead;

		lockW.writeLock().lock();
		lockR.writeLock().lock();

		try {
      	acounterWrite = counterWrite;
      	atimeWrite = timeWrite;
      	acounterRead = counterRead;
      	atimeRead = timeRead;

			counterWrite = 0;
			timeWrite = 0L;
			counterRead = 0;
			timeRead = 0L;
		   
		} finally {
			lockW.writeLock().unlock();
			lockR.writeLock().unlock();
		}
		

		System.out.println("Stats from load test with " + Configuration.getInstance().getMaxConnections() + " threads...");
		
		//print read Stats
		{
		   if (counterRead == 0) counterRead = 1;
		   float reqPsec = counterRead / (atimeRead / 1000000 / 1000);
		   float reqPmsec = counterRead / (atimeRead / 1000000 );
   		System.out.println("Read : " + counterRead + "Record with " + reqPsec + "rec/sec =" + reqPmsec + "req/ms");
		}
		/*
		//print write Stats
		{
		   if (counterRead == ) counterRead = 1;
		   float reqPsec = counterRead / (atimeRead / 1000000 / 1000);
		   float reqPmsec = counterRead / (atimeRead / 1000000 );
   		System.out.println("Read : " + counterRead + "Record with " + reqPsec + "rec/sec =" + reqPmsec + "req/ms");
		}*/


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
