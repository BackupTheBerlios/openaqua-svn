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
		lockW.readLock().lock();
		lockR.readLock().lock();
		try {
			//ns to ms
			float r =0; if (timeRead != 0)  r= timeRead  / counterRead;
			r = r / 1000000;
			//float w =0; if (timeWrite != 0) w= timeWrite  / counterWrite;

			//if (timeRead != 0) timeRead  = timeRead / 1000000;
			//if (timeWrite!= 0) timeWrite = timeWrite / 1000000;
			
			
			System.out.println("Stats from load test with " + Configuration.getInstance().getMaxConnections() + " threads");
			System.out.println("Read : "+timeRead  +"ms with "+counterRead+" Requests = "+r+" ms/req");
			//System.out.println("Write: "+timeWrite +"ms with "+counterWrite+" Requests = "+w+" ms/req");
			
		} finally {
			lockW.readLock().unlock();
			lockR.readLock().unlock();
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
