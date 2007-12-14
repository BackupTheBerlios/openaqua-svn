/**
 * 
 */
package de.tmobile.cabu;


import java.util.LinkedList;
import java.util.List;


/**
 * @author behrenan
 * 
 */
public class CAlmaDataLoader {
	private static CAlmaDataLoader INSTANCE = new CAlmaDataLoader();

	public static CAlmaDataLoader getInstances() {
		return INSTANCE;
	}

	final List<Thread> threadList = new LinkedList<Thread>();

	public CAlmaDataLoader() {
		super();

	}

	public void addList(final BaseList list) {
		final Thread thread = new Thread(new CAlmaListLoaderThread(list));
		thread.start();
		threadList.add(thread);
	}


	public void waitForFinish() {
		//First run
		for (final Thread thread : threadList) {
			try {
				thread.join();
			} catch (final InterruptedException e) {
				CLogger.getRootLogger().error("Got Exception while joining Loader threads: " + e.getMessage());
				e.printStackTrace();
			}

		}

		//Second run
		for (final Thread thread : threadList) {
			try {
				thread.join();
			} catch (final InterruptedException e) {
				CLogger.getRootLogger().error("Got Exception while joining Loader threads: " + e.getMessage());
				e.printStackTrace();
			}
		}

		threadList.clear();
	}

}
