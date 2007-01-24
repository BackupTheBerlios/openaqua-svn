/**
 * 
 */
package de.tmobile.cabu.db4o;

import java.util.Timer;

import com.db4o.Db4o;
import com.db4o.ObjectContainer;




/**
 * @author behrenan
 *
 */
public class Main {
	private static ObjectContainer database;


	/**
	 * setup a database structure
	 * @return true if fine
	 */
	private static boolean setupDatabase(){

		try {
			System.out.println("Setup faked data environment ... ");
			Db4oGenerator main = new Db4oGenerator("main", database);
			main.setupDatabase();
			main.ListAllContracts();
			System.out.println("Setup faked data environment ... done");
			return true;
		} catch (Exception e) {
			System.err.println("Exception: " + e.getMessage());
			e.printStackTrace();
		}
		return false;
	}




	/**
	 * makes the measuring
	 * @throws ClassNotFoundException 
	 *
	 */
	private static void execution ()  {		

		//setup threads
		Db4oGenerator[] threadArray = new Db4oGenerator[Configuration.getInstance().getMaxConnections()];
		for (int i = 0; i < Configuration.getInstance().getMaxConnections(); i++) {
			threadArray[i] = new Db4oGenerator( "" + i, database);
		}


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
		System.out.println( "Start Load Test with " + Configuration.getInstance().getMaxConnections()+" Threads" );
		long runTime = 0;
		
		database = Db4o.openFile("foo.dat");



		//setup Database
		if (setupDatabase() != true) {
			System.err.println("Finish after Error");

		} else {

			//and does the measuring stuff
			Timer timer = null;
			try {
				timer = new Timer();
				int count = Configuration.getInstance().getStatsAllMilliseconds();
				timer.schedule(new MinuteTimer(count), count, count);
				System.out.printf("type\t\t\treq\tmicSec\n");
				long start = System.currentTimeMillis();

				execution();
				runTime = System.currentTimeMillis() - start;
			} finally {
				timer.cancel();
			}
		}

		//Stats
		database.close();
		System.out.println( "Runtime was " +runTime + "ms");


	}

}
