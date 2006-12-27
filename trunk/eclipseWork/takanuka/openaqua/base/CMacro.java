/**
 * 
 */
package openaqua.base;
import java.util.concurrent.locks.ReentrantReadWriteLock;
import java.util.*;


/**
 * @author tukaram
 *
 */
public class CMacro implements IMacro {
	private List<ICommand> m_commands;
	final ReentrantReadWriteLock lock = new ReentrantReadWriteLock();

	public CMacro () {
		super();		
		m_commands = new LinkedList<ICommand>();
	}

	
	public void addCommand(ICommand cmd) {
		lock.writeLock().lock();
		try {
			m_commands.add(cmd);
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
	 * @param record
	 */
	public boolean execute(final IRecord record) {
		lock.readLock().lock(); //no write access to the cmd list while execution
		boolean result = true;

		try {
			ListIterator<ICommand> it = m_commands.listIterator();
			while(it.hasNext()) {
				if (it.next().execute(record) != true) {
					result = false;;
				}
			}
		} finally {
			lock.readLock().unlock();
		}
		
		return result;
	}

}
