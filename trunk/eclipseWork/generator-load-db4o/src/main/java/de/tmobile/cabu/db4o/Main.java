/**
 * 
 */
package de.tmobile.cabu.db4o;

import java.util.Timer;
import java.io.File;
import com.db4o.Db4o;
import com.db4o.ObjectContainer;
import de.tmobile.cabu.loadtest.Stats;




/**
 * @author behrenan
 *
 */
public class Main {
	private static ObjectContainer database;


	private static boolean setupDatabase(){
		return true;
	}
	/**
	 * setup a database structure
	 * @return true if fine
	 */
	private static boolean setupDatabase2(){

		try {
			System.out.println("Setup faked data environment ... ");
			Db4oGenerator main = new Db4oGenerator("main", database, false);
			main.setupDatabase();
			//main.ListAllContracts();
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
		int readInstance = 0;
		int writeInstance = 0;
		for (int i = 0; i < Configuration.getInstance().getMaxConnections(); i++) {
			if (i%2==1) {
				threadArray[i] = new Db4oGenerator( "" + i, database, true);
				readInstance++;
			} else {
				threadArray[i] = new Db4oGenerator( "" + i, database, false);
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
		System.out.println( "Start Load Test with " + Configuration.getInstance().getMaxConnections()+" Threads" );
		long runTime = 0;


		//remove old file
		System.out.println( "remove old file foo.dat file" );
		File f = new File( "foo.dat" );
		if (f.exists()) f.delete();

		
		//setup Database
		database = Db4o.openFile("foo.dat");
		if (setupDatabase() != true) {
			System.err.println("Finish after Error");
			return ;
		}
		database.close();


		//and do the measuring stuff
		database = Db4o.openFile("foo.dat");
		Timer timer = null;
		try {
			timer = new Timer();
			int count = Configuration.getInstance().getStatsAllMilliseconds();
			timer.schedule(new MinuteTimer(count), count, count);
			long start = System.currentTimeMillis();

			execution();
			runTime = System.currentTimeMillis() - start;
		} finally {
			timer.cancel();
		}
		database.close();
		
		//print a list of all stored values
		database = Db4o.openFile("foo.dat");
		Db4oGenerator main = new Db4oGenerator("main", database, false);
		main.ListAllContracts();
		database.close();

		
		System.out.println( "Runtime was " +runTime + "ms");


	}

}
