package de.openaqua.base;
import java.util.concurrent.locks.ReentrantReadWriteLock;
import java.util.*;


/**
 * @author tukaram
 *
 */
public class CMacro implements IMacro {
	private List<Integer> m_commands;
	final ReentrantReadWriteLock lock = new ReentrantReadWriteLock();

	public CMacro () {
		super();
		m_commands = new LinkedList<Integer>();
	}


	public void addCommand(Integer id) {
		lock.writeLock().lock();
		try {
			if (CFactoryCommands.getInstance().getCommand(id) == null){
				throw new IllegalArgumentException("Command Id not bound to a command");
			}
			m_commands.add(id);
		} finally {
			lock.writeLock().unlock();
		}
	}


	public void clearCommands() {
		lock.writeLock().lock();
		try {
			m_commands.clear();
		} finally {
			lock.writeLock().unlock();
		}
	}


	/**
	 * @return If one command goes wrong the result will be false, otherwise true
	 * @param context
	 */
	public boolean execute(final IContext context) {
		lock.readLock().lock(); //no write access to the cmd list while execution

		boolean result = true;
		try {
			ListIterator<Integer> it = m_commands.listIterator();
			while(it.hasNext()) {
				Integer id = it.next();
				if (CFactoryCommands.getInstance().getCommand(id).execute(context) != true) {
					result = false;
				}
			}
		} finally {
			lock.readLock().unlock();
		}

		return result;
	}

}
