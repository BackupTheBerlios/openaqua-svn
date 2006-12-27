/**
 * 
 */
package openaqua.defaultCommands;

import java.util.concurrent.locks.ReentrantReadWriteLock;

import openaqua.base.ICommand;
import openaqua.base.IRecord;

/**
 * 
 * 
 * @author tukaram
 *
 */
public class CmdUsageCounter implements ICommand{
	static int usage = 0;
	private ReentrantReadWriteLock lock = new ReentrantReadWriteLock();

	public boolean execute(IRecord record) {
		lock.writeLock().lock();
		try {
			usage++;
		} finally {
			lock.writeLock().unlock();
		}
		return true;
	}
	
	
	/**
	 * Return the collected amount of usages of this command
	 * 
	 * @return amount
	 */
	public int returnCounter() {
		return usage;
	}

	
	/**
	 * Set the counter to 0
	 *
	 */
	public void resetCounter() {
		lock.writeLock().lock();
		try {
			usage = 0;
		} finally {
			lock.writeLock().unlock();
		}
	}

}
