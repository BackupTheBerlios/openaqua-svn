/**
 * 
 */
package de.tmobile.cabu.db4o;

import java.util.Timer;




/**
 * @author behrenan
 *
 */
public class Main {


	/**
	 * setup a database structure
	 * @return true if fine
	 */
	private static boolean setupDatabase(){

		try {
			System.out.println("Setup faked data environment ... ");
			TTGenerator main = new TTGenerator("main");
			main.Init();
			main.setupDatabase();
			main.ListAllContracts();
			main.Close();
			System.out.println("Setup faked data environment ... done");
			return true;
		} catch (Exception e) {
			//System.err.println("SQLException: " + e.getMessage());
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
		TTGenerator[] threadArray = new TTGenerator[Configuration.getInstance().getMaxConnections()];
		for (int i = 0; i < Configuration.getInstance().getMaxConnections(); i++) {
			threadArray[i] = new TTGenerator( "" + i );
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
				threadArray[i].Close();
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


	/**
	 * @param args
	 * @throws InterruptedException 
	 */
	public static void main(String[] args) {
		System.out.println( "Start Load Test with " + Configuration.getInstance().getMaxConnections()+" Threads" );
		long runTime = 0;


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
		System.out.println( "Runtime was " +runTime + "ms");


	}

}
