/**
 * 
 */
package openaqua.defaultCommands;

import java.util.concurrent.locks.ReentrantReadWriteLock;

import openaqua.base.ICommand;
import openaqua.base.IRecord;

/**
 * Cmd which counts the usage of this command.<br>
 * 
 * Class is thread save and reentrant. 
 * 
 * @author tukaram
 */
public class CmdUsageCounter implements ICommand{

	/**
	 * Counts how ofte this command is used
	 */
	int usage = 0;
	
	/**
	 * Lock for thread saveness
	 */
	private ReentrantReadWriteLock lock = new ReentrantReadWriteLock();

	/*
	 * Counts how often the command(!) is used.
	 * 
	 * @see openaqua.base.ICommand#execute(openaqua.base.IRecord)
	 * @returns true
	 */
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
	public int getUsage() {
		return usage;
	}

	
	/**
	 * Set the counter to 0
	 *
	 */
	public void resetUsage() {
		lock.writeLock().lock();
		try {
			usage = 0;
		} finally {
			lock.writeLock().unlock();
		}
	}

}
