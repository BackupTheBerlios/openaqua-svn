/**
 * 
 */
package de.tmobile.cabu;

import java.sql.SQLException;
import java.util.Timer;




/**
 * @author behrenan
 *
 */
public class Main {
	static TTConnection mainConnection = null;


	/**
	 * setup a database structure
	 * @return true if fine
	 */
	private static boolean setupDatabase(){

		try {
			System.out.println("Setup faked data environment ... ");
			mainConnection.CreateTableStructure();
			System.out.println("Setup faked data environment ... done");
			return true;
		} catch (SQLException e) {
			System.err.println("SQLException: " + e.getMessage());
			e.printStackTrace();
			
		}
		return false;
	}




	/**
	 * makes the measuring
	 * @throws ClassNotFoundException 
	 *
	 */
	private static void execution () throws ClassNotFoundException {		

		//setup threads
		TTGenerator[] threadArray = new TTGenerator[Configuration.getInstance().getMaxConnections()];
		for (int i = 0; i < Configuration.getInstance().getMaxConnections(); i++) {
			boolean readTest;
			if (i%2==1) {
				readTest=true;
			} else {
				readTest=false;
			}
			threadArray[i] = new TTGenerator( "" + i, readTest);
			threadArray[i].Init();
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
			//System.out.println( "Finished Generator Run with Connection ID " + getName());
		}
		long diff = System.nanoTime()-Stats.getInstance().getGlobalTime();

		//print stat infos
		double ms = diff/1000000; //yepp, durch 10000. Oder???
		double msP = ms/Configuration.getInstance().getMaxConnections();
		System.out.println( "Finished Load Test in " + ms +" ms = " + msP + " ms/Connection ");

	}


	/**
	 * @param args
	 * @throws InterruptedException 
	 */
	public static void main(String[] args) throws InterruptedException {
		System.out.println( "Start Load Test with " + Configuration.getInstance().getMaxConnections()+" Threads" );
		long runTime = 0;

		try {
			mainConnection = new TTConnection();
			mainConnection.Connect();
		} catch (ClassNotFoundException e1) {
			System.err.println("Java ClassNotFound: " + e1.getMessage());
			return;
		} catch (SQLException e) {
			System.err.println("SQLException: " + e.getMessage());
			e.printStackTrace();
		}


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
				System.out.printf("type\t\t\treq\tµs\n");
				long start = System.currentTimeMillis();

				execution();
				runTime = System.currentTimeMillis() - start;
			} catch (ClassNotFoundException e) {
				System.err.println( "Run was aborted by an exception");
				e.printStackTrace();
			} finally {
				timer.cancel();
			}
		}

		//Stats
		System.out.println( "Runtime was " +runTime + "ms");
		mainConnection.Disconnect();


	}

}
