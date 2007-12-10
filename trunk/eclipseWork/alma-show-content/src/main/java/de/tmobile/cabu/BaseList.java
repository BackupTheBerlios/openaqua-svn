/**
 * 
 */
package de.tmobile.cabu;


import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.TreeMap;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;


/**
 * @author behrenan
 * 
 */
public abstract class BaseList extends TreeMap<Integer, BaseType> {
	private final ReadWriteLock lock = new ReentrantReadWriteLock();
	private final Lock readLock = lock.readLock();
	private final Lock writeLock = lock.writeLock();


	protected BaseList() {
		super();
	}


	@Override
	public void clear() {
		writeLock.lock();
		try {
			super.clear();
		} finally {
			writeLock.unlock();
		}
	}

	@Override
	public BaseType get(final Object key) {
		readLock.lock();
		try {
			return super.get(key);
		} finally {
			readLock.unlock();
		}
	}

	abstract public String getPrintDescription();

	abstract public String getPrintHeader(final String prefix);

	abstract protected String getQueryString();


	abstract protected void HandleQueryResult(ResultSet rs) throws SQLException;

	final public void print(final String prefix) {
		final String desc = getPrintDescription();
		final String head = getPrintHeader(prefix);

		if (desc != null && desc.length() > 0) {
			CLogger.getRootLogger().emptyLine();
			CLogger.getRootLogger().out(desc);
		}

		if (head != null && head.length() > 0) {
			CLogger.getRootLogger().emptyLine();
			CLogger.getRootLogger().out(head);
		}
		printElements(prefix);
	}

	final public void printElements(final String prefix) {
		readLock.lock();
		try {
			for (final BaseType type : values()) {
				CLogger.getRootLogger().out(type.getPrintString(prefix));
			}
		} finally {
			readLock.unlock();
		}
	}


	final protected void refreshList() throws SQLException {
		if (CConfiguration.getInstance().isError()) { return; }
		if (getQueryString() == null) { return; }
		clear(); //attention: makes a lock too!

		// exec SQL command
		final Statement stmt = CConfiguration.getInstance().getConnection().createStatement();
		final ResultSet rs = stmt.executeQuery(getQueryString());
		writeLock.lock();
		try {
			HandleQueryResult(rs);
		} finally {
			writeLock.unlock();
			rs.close();
			stmt.close();
		}
	}

	/**
	 * @param error
	 *           the error to set
	 */

	final public void store(final BaseType type) {
		readLock.lock();
		try {
			put(type.getId(), type);
		} finally {
			readLock.unlock();
		}
	}
}
