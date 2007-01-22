/**
 * 
 */
package de.tmobile.cabu.db4o;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.UnknownHostException;
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
	private static byte[] loadBuffer(){
		//read in buffer
		byte[] rawBuffer = null; 
		try {
			File f = new File( "data.raw" ); 
			rawBuffer = new byte[ (int) f.length() ];
			if (f.length() < 10 ) {
				System.err.println("file data.raw seams to be to short");
				return null;
			}
			InputStream in = new FileInputStream( f ); 
			in.read( rawBuffer );
			in.close();
		} catch (Exception e) {
			System.err.println("file data.raw not found");
			return null;
		} 
		return rawBuffer;
	}




	/**
	 * makes the measuring
	 * @throws ClassNotFoundException 
	 * @throws IOException 
	 * @throws UnknownHostException 
	 *
	 */
	private static void execution (byte[] rawBuffer) throws IOException {		

		//setup threads
		
		AlmaGenerator[] threadArray = new AlmaGenerator[Configuration.getInstance().getMaxConnections()];
		for (int i = 0; i < Configuration.getInstance().getMaxConnections(); i++) {
			try {
				threadArray[i] = new AlmaGenerator(rawBuffer, "" + i );
				threadArray[i].Init();
			} catch (UnknownHostException e) {
				System.err.println("Error while connection init: " + e.getLocalizedMessage());
			}
			
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
	 * @throws IOException 
	 * @throws UnknownHostException 
	 */
	public static void main(String[] args) throws InterruptedException, UnknownHostException, IOException {
		System.out.println( "Start Load Test with " + Configuration.getInstance().getMaxConnections()+" Threads" );
		System.out.println( "Hint: Error messages Broken Pipe means prop that alma did not accept a certain connection");
		long runTime = 0;

		byte[] rawBuffer = null;
		rawBuffer = loadBuffer();
		//setup Database
		if (rawBuffer == null) {
			System.err.println("Error while loading data.raw file. Test aborted");
		} else {

			//and does the measuring stuff
			Timer timer = null;
			try {
				timer = new Timer();
				int count = Configuration.getInstance().getStatsAllMilliseconds();
				timer.schedule(new MinuteTimer(count), count, count);
				System.out.printf("type\t\t\treq\tµsec\n");
				long start = System.currentTimeMillis();
				
				//fire up the worker threads:
				execution(rawBuffer);
				
				//measuring done ...
				runTime = System.currentTimeMillis() - start;
			} finally {
				timer.cancel();
			}
		}

		//Stats
		System.out.println( "Runtime was " +runTime + "ms");


	}

}
