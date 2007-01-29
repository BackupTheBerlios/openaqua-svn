/**
 * 
 */
package de.tmobile.cabu.db4o;

import java.io.IOException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import org.apache.log4j.Logger;
import com.db4o.Db4o;
import com.db4o.ObjectContainer;
import com.db4o.ObjectServer;


import de.tmobile.cabu.db4o.EmbeddedServerConfiguration.UserPasswordPair;


final public class DatabaseServerRegistry {
	private Map<String, ObjectServer> mapKey2Server;
	private Map<String, EmbeddedServerConfiguration> mapKey2Config;
	final private static Logger logger = Logger.getRootLogger();
	final static private DatabaseServerRegistry Instance = new DatabaseServerRegistry(); 



	/**
	 * 
	 *
	 */
	private DatabaseServerRegistry() {
		super();
		mapKey2Server = new HashMap<String, ObjectServer>();
		mapKey2Config = new HashMap<String, EmbeddedServerConfiguration>();
	}


	/**
	 * @return the instance
	 */
	public static final DatabaseServerRegistry getInstance() {
		return Instance;
	}


	/*
	 */
	public synchronized  void registerServer(String pKey, EmbeddedServerConfiguration configuration)	throws EDatabaseAlreadyRegistered {
		if (mapKey2Server.containsKey(pKey)) throw (new EDatabaseAlreadyRegistered("Database key"+pKey+" already registered"));
		ObjectServer s = Db4o.openServer(configuration.getFilename(), configuration.getPort());
		for(Iterator<UserPasswordPair> i = configuration.getUsers().listIterator(); i.hasNext();) {
			EmbeddedServerConfiguration.UserPasswordPair pair = i.next();
			s.grantAccess(pair.user, pair.password);
		}
		
		mapKey2Server.put(pKey, s);
		mapKey2Config.put(pKey, configuration);
		logger.info("Object Server with key \""+pKey+"\" running");
	}


	/*
	 * @result null if key unknown, otherwise a server reference
	 */
	public synchronized ObjectContainer getClient(final String key) {
		EmbeddedServerConfiguration c = mapKey2Config.get(key);
		ObjectServer s = mapKey2Server.get(key);
		if (s==null) return null;
		if (c==null) return null;
		
		//local, embedded client?
		if (c.getPort() == 0) {
			return s.openClient();
		}

		return null;
		
	}

	/*
	 * @result null if key unknown, otherwise a server reference
	 */
	public synchronized ObjectContainer getClient(String key, String username, String password) throws IOException {
		EmbeddedServerConfiguration c = mapKey2Config.get(key);
		ObjectServer s = mapKey2Server.get(key);
		
		if (s==null) {
			logger.error("No Server for given key \""+key+"\" found");
			return null;
		}
		if (c==null) {
			logger.error("No Configuration for given key \""+key+"\" found");
			return null;
		}
		
		ObjectContainer oc = Db4o.openClient(c.getHostname(), c.getPort(), username, password);

		return oc;		
	}


	public synchronized String getFilenameForKey(final String key) {
		//EmbeddedServerThread s = mapKey2Server.get(key);
		//if (s == null) return null;
		//return s.getDatabaseFilename();
		return null;
	}

	/*
	 * Stop all known servers but don't remove them from the system.<br>
	 * It is possible to restart them
	 */
	public synchronized void stopAndRemoveAllServers() {
		Set<String> keys = mapKey2Server.keySet();

		for (Iterator i = keys.iterator(); i.hasNext();) {
			String key = (String)i.next();
			ObjectServer s = mapKey2Server.get(key);
			s.close();
		}

		mapKey2Server.clear();
		mapKey2Config.clear();
	}
	
}
