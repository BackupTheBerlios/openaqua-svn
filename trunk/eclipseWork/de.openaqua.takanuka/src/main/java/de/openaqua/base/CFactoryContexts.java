package de.openaqua.base;

import java.util.HashMap;
import java.util.concurrent.locks.ReentrantReadWriteLock;


/**
 *
 */
final public class CFactoryContexts {
	final private static CFactoryContexts INSTANCE = new CFactoryContexts();
	private HashMap<Integer, IContext> m_recordMap = new HashMap<Integer, IContext>();
	private ReentrantReadWriteLock lock = new ReentrantReadWriteLock(true);

	/**
	 * Private constructor. The Factory is a singleton. For getting an instance
	 * use the {@code getInstance() } methods
	 *
	 * @see #getInstance()
	 *
	 */
	private CFactoryContexts() {
		super();
	}


	/**
	 *
	 * @return a reference to a singleton instance of this factory
	 */
	final public static CFactoryContexts getInstance() {
		return INSTANCE;
	}


	/**
	 *
	 * @param id
	 * @param prototype
	 */
	public void addRecordPrototyp(int id, IContext prototype) {
		//check for null pointer
		if (prototype == null) {
			throw new java.lang.NullPointerException("CFactoryRecords.addRecordPrototyp() called with null value");
		}

		lock.writeLock().lock();
		try {
			m_recordMap.put(id, prototype);
		} finally {
			lock.writeLock().unlock();
		}
	}



	/**
	 * removes the record prototype for a given ID
	 * @param id the record id
	 */
	public void removeRecordPrototyp(int id) {
		lock.writeLock().lock();
		try {
			if (m_recordMap.containsKey(id)){
				m_recordMap.remove(id);
			}
		} finally {
			lock.writeLock().unlock();
		}
	}



	/**
	 * Remove all record prototyps
	 */
	public void clearPrototyps() {
		lock.writeLock().lock();
		try {
			m_recordMap.clear();
		} finally {
			lock.writeLock().unlock();
		}
	}




	/**
	 * Returns a new record. If there isn't a prototype for the
	 * given Id the method returns a null reference.
	 *
	 * @param id
	 * @return the context record for the given id
	 */
	public IContext getRecord (int id) {
		IContext result;
		lock.readLock().lock();
		try {
			result = m_recordMap.get(id).clone();
		} finally {
			lock.readLock().unlock();
		}
		return result;
	}
}

