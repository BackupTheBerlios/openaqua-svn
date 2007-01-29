/**
 * 
 */
package de.tmobile.cabu.db4o;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import org.apache.log4j.Logger;
import com.db4o.Db4o;
import com.db4o.ObjectContainer;
import com.db4o.ObjectServer;
import com.db4o.messaging.MessageSender;

final public class Db4oDatabaseRegistry implements Runnable{
	private Map<String, ObjectServer> mapKey2Server;
	private Map<ObjectServer, String> mapServer2File;
	final private static Logger logger = Logger.getRootLogger();
	final static private Db4oDatabaseRegistry Instance = new Db4oDatabaseRegistry(); 
2


	/**
	 * 
	 *
	 */
	private Db4oDatabaseRegistry() {
		super();
		mapKey2Server = new HashMap<String, ObjectServer>();
		mapServer2File = new HashMap<ObjectServer, String>();
	}


	/**
	 * @return the instance
	 */
	public static final Db4oDatabaseRegistry getInstance() {
		return Instance;
	}


	/*
	 */
	public synchronized  ObjectServer registerDatabasefile(String pKey, String databaseFile)	throws EDatabaseAlreadyRegistered {

		if (pKey == null)			throw new NullPointerException("key value was null while registering a database file");
		if (databaseFile == null)	throw new NullPointerException("databaseFile value was null while registering a database file");
		if (mapKey2Server.containsKey(pKey)) 			throw (new EDatabaseAlreadyRegistered("Database key"+pKey+" already registered"));
		if (mapServer2File.containsValue(databaseFile)) throw (new EDatabaseAlreadyRegistered("Database file"+databaseFile+" used for other key"));

		logger.info("registerDatabasefile \""+databaseFile+"\" for key \""+ pKey + "\"");

		ObjectServer s = Db4o.openServer(databaseFile, 0);
		mapKey2Server.put(pKey, s);
		mapServer2File.put(s, databaseFile);
		logger.info("Object Server with key \""+pKey+"\" running");

		return s;
	}


	/*
	 * @result null if key unknown, otherwise a server reference
	 */
	public synchronized ObjectContainer getClient(final String key) {
		ObjectServer s = mapKey2Server.get(key);
		if (s==null) return null;
		return s.openClient();
	}


	public synchronized String getFilenameForKey(final String key) {
		ObjectServer s = mapKey2Server.get(key);
		if (s == null) return null;
		return mapServer2File.get(s);
	}

	/*
	 * Stop all known servers but don't remove them from the system.<br>
	 * It is possible to restart them
	 */
	public synchronized void stopAndRemoveAllServers() {
		Set<String> keys = mapKey2Server.keySet();

		for (Iterator i = keys.iterator(); i.hasNext();) {
			String key = (String)i.next();
			
			ObjectContainer c = mapKey2Server.get(key).openClient();
			if (c != null) {
				MessageSender messageSender = c.ext().configure().getMessageSender();
				messageSender.send(new StopServer());
				
			}
			logger.info("Object Server with key \""+key+"\" closed");
		}

		mapKey2Server.clear();
		mapServer2File.clear();
	}
	
	public void run() {
		
	}


}
