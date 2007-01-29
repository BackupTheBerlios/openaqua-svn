/**
 * 
 */
package de.tmobile.cabu.db4o;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import org.apache.log4j.Logger;
import com.db4o.ObjectContainer;


final public class Db4oDatabaseRegistry {
	private Map<String, EmbeddedServerThread> mapKey2Server;
	final private static Logger logger = Logger.getRootLogger();
	final static private Db4oDatabaseRegistry Instance = new Db4oDatabaseRegistry(); 



	/**
	 * 
	 *
	 */
	private Db4oDatabaseRegistry() {
		super();
		mapKey2Server = new HashMap<String, EmbeddedServerThread>();
	}


	/**
	 * @return the instance
	 */
	public static final Db4oDatabaseRegistry getInstance() {
		return Instance;
	}


	/*
	 */
	public synchronized  void registerDatabasefile(String pKey, EmbeddedServerConfiguration configuration)	throws EDatabaseAlreadyRegistered {
		if (mapKey2Server.containsKey(pKey)) throw (new EDatabaseAlreadyRegistered("Database key"+pKey+" already registered"));
		EmbeddedServerThread s = new EmbeddedServerThread(configuration);
		mapKey2Server.put(pKey, s);
		logger.info("Object Server with key \""+pKey+"\" running");
	}


	/*
	 * @result null if key unknown, otherwise a server reference
	 */
	public synchronized ObjectContainer getClient(final String key) {
		EmbeddedServerThread s = mapKey2Server.get(key);
		if (s==null) return null;
		return s.getClient();
	}


	public synchronized String getFilenameForKey(final String key) {
		EmbeddedServerThread s = mapKey2Server.get(key);
		if (s == null) return null;
		return s.getDatabaseFilename();
	}

	/*
	 * Stop all known servers but don't remove them from the system.<br>
	 * It is possible to restart them
	 */
	public synchronized void stopAndRemoveAllServers() {
		Set<String> keys = mapKey2Server.keySet();

		for (Iterator i = keys.iterator(); i.hasNext();) {
			String key = (String)i.next();
			mapKey2Server.get(key).close();
		}

		mapKey2Server.clear();
	}
	
}
