/**
 * 
 */
package de.tmobile.cabu;


import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;


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
		final Thread thread = new Thread(list);
		thread.start();
		threadList.add(thread);
	}

	public void clear() {
		threadList.clear();

	}

	public void join() {
		ListIterator<Thread> iter;

		//First run
		iter = threadList.listIterator();
		while (iter.hasNext()) {
			try {
				iter.next().join();
			} catch (final InterruptedException e) {
				Logger.getRootLogger().error("Got Exception while joining Loader threads: " + e.getMessage());
				e.printStackTrace();
			}
		}

		//2nd run
		iter = threadList.listIterator();
		while (iter.hasNext()) {
			try {
				iter.next().join();
			} catch (final InterruptedException e) {
				Configuration.getInstance().getConnection().Disconnect();
				Logger.getRootLogger().error("Got Exception while joining Loader threads: " + e.getMessage());
				e.printStackTrace();

			}
		}
	}
}
