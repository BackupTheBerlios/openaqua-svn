/**
 * 
 */
package de.tmobile.cabu.db4o;

import java.util.Timer;
import java.io.File;

import org.apache.log4j.ConsoleAppender;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.apache.log4j.PatternLayout;
import de.tmobile.cabu.loadtest.Stats;
import de.tmobile.cabu.loadtest.MinuteTimer;
import de.tmobile.cabu.loadtest.Configuration;




public class Main {
	static String key = new String("test");
	final private static Logger logger = Logger.getRootLogger();


	/**
	 * setup a database structure
	 * @return true if fine
	 */
	private static boolean setupDatabase(final String filename){
		boolean result = false;

		//remove old file
		System.out.println( "remove old file foo.dat file" );
		File f = new File( filename );
		if (f.exists()) f.delete();
		Db4oDatabaseRegistry.getInstance().registerDatabasefile(key, "foo.dat");

		
		//setup new
		try {
			logger.info("Setup new database ... ");
			Db4oGenerator main = new Db4oGenerator("main", key, false);
			main.setupDatabase();
			System.out.println("Setup new database ... done ");
			result = true;
		} catch (Exception e) {
			System.err.println("Exception: " + e.getMessage());
			e.printStackTrace();
		}
		return result;
	}




	/**
	 * makes the measuring
	 * @throws ClassNotFoundException 
	 *
	 */
	private static void execution ()  {		

		//setup threads
		Db4oGenerator[] threadArray = new Db4oGenerator[Configuration.getInstance().getMaxConnections()];
		int readInstance = 0;
		int writeInstance = 0;
		for (int i = 0; i < Configuration.getInstance().getMaxConnections(); i++) {
			if (i%2==1) {
				threadArray[i] = new Db4oGenerator( "" + i, key, false);
				readInstance++;
			} else {
				threadArray[i] = new Db4oGenerator( "" + i, key, false);
				writeInstance++;
			}
		}
		System.out.println("Read  Access Threads: " + readInstance);
		System.out.println("Write Access Threads: " + writeInstance);
		


		//fire up all threads
		Stats.getInstance().setGlobalTime(System.nanoTime());
		for (int i = 0; i < Configuration.getInstance().getMaxConnections(); i++) {
			threadArray[i].start();
		}

		//wait for finish
		for (int i = 0; i < Configuration.getInstance().getMaxConnections(); i++) {
			try {
				threadArray[i].join();
			} catch (InterruptedException e) {
				System.err.println("Error while joining a thread");
				e.printStackTrace();
			}
		}
		long diff = System.nanoTime()-Stats.getInstance().getGlobalTime();

		//print stat infos
		double ms = diff/1000000; //yepp, durch 10000. Oder???
		double msP = ms/Configuration.getInstance().getMaxConnections();
		System.out.println( "Finished Load Test in " + ms +" ms = " + msP + " ms/Connection ");
		

	}


	public static void main(String[] args) {
		PatternLayout layout = new PatternLayout( "%-5p [%t] %C{1}:%L -> %m%n" );
		//PatternLayout layout = new PatternLayout( "%F:%L %-5p [%t] %C{1} -> %m%n" );
		ConsoleAppender consoleAppender = new ConsoleAppender( layout );
		logger.addAppender( consoleAppender );
		logger.setLevel( Level.ALL);
		
		logger.info( "Start Load Test with " + Configuration.getInstance().getMaxConnections()+" Threads" );
		long runTime = 0;
		final String filename = "foo.dat";


		
		//setup Database
		if ((Configuration.getInstance().isSetupDatabase() == true) && (setupDatabase(filename) != true)) {
			System.err.println("Finish after Error");
			return ;
		} 

		
		//and do the measuring stuff
		Timer timer = null;
		try {
			timer = new Timer();
			int count = Configuration.getInstance().getStatMilliSeconds();
			timer.schedule(new MinuteTimer(count), count, count);
			long start = System.currentTimeMillis();

			execution();
			runTime = System.currentTimeMillis() - start;
		} finally {
			timer.cancel();
		}
		
		//print a list of all stored values
		Db4oGenerator main = new Db4oGenerator("main", key, false);
		main.ListAllContracts();
		
		Db4oDatabaseRegistry.getInstance().stopAllServers();
		logger.info( "================Runtime was " +runTime + "ms");


	}

}
