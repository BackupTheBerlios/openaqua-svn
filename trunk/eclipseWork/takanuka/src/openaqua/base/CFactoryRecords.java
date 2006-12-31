package openaqua.base;

import java.util.HashMap;
import java.util.concurrent.locks.ReentrantReadWriteLock;


/**
 * TODO Add a Record Reset
 * TODO Add Doc
 * TODO Add Unit Test 
 * @author tukaram
 *
 */
final public class CFactoryRecords {
	final private static CFactoryRecords INSTANCE = new CFactoryRecords();
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
		super();
	}
	
	
	/** 
	 * 
	 * @return a reference to a singleton instance of this factory
	 */
	final public static CFactoryRecords getInstance() {
		return INSTANCE;
	}
	
	
	/**
	 * 
	 * @param id
	 * @param prototype
	 */
	public void addRecordPrototyp(int id, IRecord prototype) {
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

