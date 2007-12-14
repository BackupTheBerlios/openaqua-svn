/**
 * 
 */
package de.tmobile.cabu;


import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.locks.ReentrantLock;


/**
 * @author behrenan
 * 
 */
public class CAlmaDataLoader {
	private static CAlmaDataLoader INSTANCE = new CAlmaDataLoader();

	public static CAlmaDataLoader getInstances() {
		return INSTANCE;
	}
	private final ReentrantLock lock = new ReentrantLock();

	final List<Thread> threadList = new LinkedList<Thread>();

	public CAlmaDataLoader() {
		super();

	}

	public void addList(final BaseList list) {
		lock.lock();
		try {
			final Thread thread = new Thread(new CAlmaListLoaderThread(list));
			thread.start();
			threadList.add(thread);
		} finally {
			lock.unlock();
		}
	}

	public void clear() {
		lock.lock();
		//clean up
		try {
			threadList.clear();
		} finally {
			lock.unlock();
		}

	}


	public boolean isLoading() {
		lock.lock();
		try {
			return !threadList.isEmpty();
		} finally {
			lock.unlock();
		}
	}

	public void join() {
		lock.lock();

		try {

			//First run
			for (final Thread thread : threadList) {
				try {
					thread.join();
				} catch (final InterruptedException e) {
					CLogger.getRootLogger().error("Got Exception while joining Loader threads: " + e.getMessage());
					e.printStackTrace();
				}

			}

			//First run
			for (final Thread thread : threadList) {
				try {
					thread.join();
				} catch (final InterruptedException e) {
					CLogger.getRootLogger().error("Got Exception while joining Loader threads: " + e.getMessage());
					e.printStackTrace();
				}
			}

			//clean up
		} finally {
			lock.unlock();
		}
	}

}
