/**
 * 
 */
package de.tmobile.cabu.db4o;

import com.db4o.Db4o;
import com.db4o.ObjectContainer;
import com.db4o.ObjectServer;


/**
 * @author behrenan
 *
 */
final public class EmbeddedServerThread implements Runnable{
	//final private static Logger logger = Logger.getRootLogger();
	final private EmbeddedServerConfiguration configuration;
	final private ObjectServer db4oServer;



	public EmbeddedServerThread (final EmbeddedServerConfiguration configuration) {
		super();
		this.configuration = configuration;
		Db4o.configure().lockDatabaseFile(true);
		Db4o.configure().clientServer().singleThreadedClient(false);
		this.db4oServer = Db4o.openServer(this.configuration.getFilename(), 10000);
	}


	public String getDatabaseFilename() {
		return configuration.getFilename();
	}


	public void run() {
		Thread.currentThread().setName(this.getClass().getName());
		Thread.currentThread().setPriority(Thread.MIN_PRIORITY); //db4oserver has its own thread
	}

	public ObjectContainer getClient() {
		return db4oServer.openClient();
	}

	public void close(){
		db4oServer.close();
	}
}	

