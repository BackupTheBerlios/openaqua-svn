package openaqua.base;

import java.util.Map;
import java.util.concurrent.locks.Lock;


/**
 * 
 * @author tukaram
 *
 */
public class CFactoryRecords {
	private final static CFactoryRecords INSTANCE = new CFactoryRecords();
	private Map<Integer, IRecord> m_recordMap;
	private Lock lock;
	
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
	public CFactoryRecords getInstance() {
		return INSTANCE;
	}
	
	
	/**
	 * 
	 * @param id
	 * @param prototype
	 */
	public void addRecordPrototyp(int id, IRecord prototype) {
		lock.lock();
		try {
			m_recordMap.put(id, prototype);
		} finally {
			lock.unlock();
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
		return m_recordMap.get(id).clone();
	}
}

