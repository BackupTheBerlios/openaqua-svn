/**
 * 
 */
package de.openaqua.vwl;


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

	protected CAlmaDataLoader() {
		super();

	}

	final public void addList(final BaseList list) {
		final Thread thread = makeNewThread(null, list);
		thread.start();
		threadList.add(thread);
	}

	final public void addList(final String name, final BaseList list) {
		final Thread thread = makeNewThread(name, list);
		thread.start();
		threadList.add(thread);
	}


	public Thread makeNewThread(final String name, final BaseList list) {
		//param name will be ignored
		return new Thread(new CAlmaListLoaderThread(list));
	}


	final public void waitForFinish() {
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
