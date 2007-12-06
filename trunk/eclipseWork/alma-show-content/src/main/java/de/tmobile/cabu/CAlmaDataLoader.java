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
public class AlmaDataLoader {
	private static AlmaDataLoader INSTANCE = new AlmaDataLoader();

	public static AlmaDataLoader getInstances() {
		return INSTANCE;
	}
	final List<Thread> threadList = new LinkedList<Thread>();

	public AlmaDataLoader() {
		super();

	}

	public void addList(final CBaseList list) {
		final Thread thread = new Thread(new AlmaListLoaderThread(list));
		thread.start();
		threadList.add(thread);
	}

	public void clear() {
		threadList.clear();

	}

	public void join() {

		//First run
		for (final Thread thread : threadList) {
			try {
				thread.join();
			} catch (final InterruptedException e) {
				Logger.getRootLogger().error("Got Exception while joining Loader threads: " + e.getMessage());
				e.printStackTrace();
			}

		}

		//First run
		for (final Thread thread : threadList) {
			try {
				thread.join();
			} catch (final InterruptedException e) {
				Logger.getRootLogger().error("Got Exception while joining Loader threads: " + e.getMessage());
				e.printStackTrace();
			}

		}
	}
}
