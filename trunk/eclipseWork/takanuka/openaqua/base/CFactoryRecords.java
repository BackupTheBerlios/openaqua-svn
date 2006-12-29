package openaqua.base;

import java.util.HashMap;
import java.util.concurrent.locks.ReentrantReadWriteLock;


/**
 * 
 * @author tukaram
 *
 */
final public class CFactoryRecords {
	private final static CFactoryRecords INSTANCE = new CFactoryRecords();
	private HashMap<Integer, IRecord> m_recordMap = new HashMap<Integer, IRecord>();
	private ReentrantReadWriteLock lock = new ReentrantReadWriteLock(true);
	
	/**
	 * Private constructor. The Factory is a singleton. For getting an instance
	 * use the {@code getInstance() } methods
	 * 
	 * @see getInstance();
	 *
	 */
	private CFactoryRecords() {
		//empty
	}
	
	
	/** 
	 * 
	 * @return a reference to a singleton instance of this factory
	 */
	public static CFactoryRecords getInstance() {
		return INSTANCE;
	}
	
	
	/**
	 * 
	 * @param id
	 * @param prototype
	 */
	public void addRecordPrototyp(int id, IRecord prototype) {
		lock.writeLock().lock();
		try {
			m_recordMap.put(id, prototype);
		} finally {
			lock.writeLock().unlock();
		}
	}
	
	
	/**
	 * Returns a new record. If there isn't a prototype for the
	 * given Id the method returns a null reference.
	 * 
	 * @param id
	 * @return
	 */
	public IRecord getRecord (int id) {
		IRecord result;
		lock.readLock().lock();
		try {
			result = m_recordMap.get(id).clone();
		} finally {
			lock.readLock().unlock();
		}
		return result;		
	}
}
