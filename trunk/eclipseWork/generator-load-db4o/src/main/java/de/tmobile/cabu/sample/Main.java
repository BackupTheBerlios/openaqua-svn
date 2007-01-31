/**
 * 
 */
package de.tmobile.cabu.sample;

import java.util.Timer;
import java.io.File;
import java.io.IOException;

import org.apache.log4j.ConsoleAppender;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.apache.log4j.PatternLayout;

import com.db4o.Db4o;
import com.db4o.io.MemoryIoAdapter;

import de.tmobile.cabu.db4o.DatabaseServerRegistry;
import de.tmobile.cabu.db4o.ServerConfiguration;
import de.tmobile.cabu.loadtest.MinuteTimer;
import de.tmobile.cabu.loadtest.Configuration;




public class Main {
	final static String serverKey = "testDatabase";
	final static String filename = "foo.dat"; 
	final private static Logger logger = Logger.getRootLogger();
	static ServerConfiguration conf = null;
	


	public static void main(String[] args) throws IOException {
		
		//setup log4j config
		PatternLayout layout = new PatternLayout( "%-5p [%t] %C{1}:%L -> %m%n" );
		//PatternLayout layout = new PatternLayout( "%F:%L %-5p [%t] %C{1} -> %m%n" );
		ConsoleAppender consoleAppender = new ConsoleAppender( layout );
		logger.addAppender( consoleAppender );
		logger.setLevel( Level.ALL);
		long runTime = 0;
		
		
		//remove old database file
		new File(filename).delete();
		//if (f.exists()) f.delete();

		Db4o.configure().io(new MemoryIoAdapter ());
		
		
		//setup ObjectServer
		Db4o.configure().callConstructors(true);
		//Db4o.configure().lockDatabaseFile(true);
		//Db4o.configure().objectClass(Contract.class).objectField("contractKey").indexed(true);
		//Db4o.configure().objectClass(ContractKey.class).objectField("key").indexed(true);
		//Db4o.configure().callbacks(false);
		Db4o.configure().blockSize(8);
		
		
		conf = new ServerConfiguration(filename, 10000, "localhost");
		//conf = new ServerConfiguration(filename, 0, "localhost");
		final String username = "test";
		final String password = "test";
		conf.addUser(username, password);
		DatabaseServerRegistry.getInstance().registerServer(serverKey, conf);

		
		logger.info( "Start Load Test with " + Configuration.getInstance().getMaxConnections()+" Threads" );

		//create an initial setup for the database file
		if ((Configuration.getInstance().isSetupDatabase() ) && (setupDatabase() != true)) {
			System.err.println("Finish after Error");
			return ;
		} 

		
		//and do the measuring stuff
		Timer timer = new Timer();
		try {
			int count = Configuration.getInstance().getStatMilliSeconds();
			timer.schedule(new MinuteTimer(count), count, count);
			long start = System.currentTimeMillis();
			execution();
			runTime = System.currentTimeMillis() - start;
		} finally {
			timer.cancel();
		}
		
		//print a list of all stored values
		//Db4oGenerator main = new Db4oGenerator("main", serverKey, false);
		//main.ListAllContracts();
		
		DatabaseServerRegistry.getInstance().stopAndRemoveAllServers();
		logger.info( "================Runtime was " +runTime + "ms");


	}

	/**
	 * makes the measuring
	 * @throws IOException 
	 * @throws ClassNotFoundException 
	 *
	 */
	private static void execution () throws IOException  {		

		//setup all threads
		Db4oGenerator[] threadArray = new Db4oGenerator[Configuration.getInstance().getMaxConnections()];
		int readInstance = 0;
		int writeInstance = 0;
		for (int i = 0; i < Configuration.getInstance().getMaxConnections(); i++) {
			if (i%2==1) {		threadArray[i] = new Db4oGenerator( "" + i, serverKey, true);
								readInstance++;
			} else {			threadArray[i] = new Db4oGenerator( "" + i, serverKey, false);
								writeInstance++;
			}
		}
		logger.info("Read  Access Threads: " + readInstance);
		logger.info("Write Access Threads: " + writeInstance);
		

		//fire up all threads
		for (int i = 0; i < Configuration.getInstance().getMaxConnections(); i++) 	threadArray[i].start();

		//wait for finish
		for (int i = 0; i < Configuration.getInstance().getMaxConnections(); i++) {
			try {
				threadArray[i].join();
			} catch (InterruptedException e) {
				logger.error("Error while joining a thread");
				e.printStackTrace();
			}
		}
	}

	/**
	 * setup a database structure
	 * @return true if fine
	 */
	private static boolean setupDatabase(){
		boolean result = false;
		
		//setup new
		try {
			logger.info("Setup new database ... ");
			Db4oGenerator main = new Db4oGenerator("main", serverKey, false);
			main.setupDatabase();
			logger.info("Setup new database ... done ");
			result = true;
		} catch (Exception e) {
			System.err.println("Exception: " + e.getMessage());
			e.printStackTrace();
		}
		
		//DatabaseServerRegistry.getInstance().stopAndRemoveAllServers();
		return result;
	}




	
}
