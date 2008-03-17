/**
 * 
 */
package de.tmobile.cabu.alma;


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
	 * makes the measuring
	 * 
	 * @throws ClassNotFoundException
	 * @throws IOException
	 * @throws UnknownHostException
	 * 
	 */
	private static void execution(final byte[] rawBuffer) throws IOException {

		//setup threads

		final AlmaGenerator[] threadArray = new AlmaGenerator[Configuration.getInstance().getMaxConnections()];
		for (int i = 0; i < Configuration.getInstance().getMaxConnections(); i++) {
			try {
				threadArray[i] = new AlmaGenerator(rawBuffer, "" + i);
				threadArray[i].Init();
			} catch (final UnknownHostException e) {
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
			} catch (final InterruptedException e) {
				System.err.println("Error while joining a thread");
				e.printStackTrace();
			}
			//System.out.println( "Finished Generator Run with Connection ID " + getName());
		}
		final long diff = System.nanoTime() - Stats.getInstance().getGlobalTime();

		//print stat infos
		final double ms = diff / 1000000; //yepp, durch 10000. Oder???
		final double msP = ms / Configuration.getInstance().getMaxConnections();
		System.out.println("Finished Load Test in " + ms + " ms = " + msP + " ms/Connection ");

	}


	/**
	 * setup a database structure
	 * 
	 * @return true if fine
	 */
	private static byte[] loadBuffer(final String filename) {
		//read in buffer
		byte[] rawBuffer = null;
		try {
			final File f = new File(filename);
			if (!f.canRead()) {
				System.err.println("Cannot read file " + filename);
				return null;
			}
			rawBuffer = new byte[(int) f.length()];
			if (f.length() < 10) {
				System.err.println("file " + filename + " seams to be to short");
				return null;
			}
			final InputStream in = new FileInputStream(f);
			in.read(rawBuffer);
			in.close();
		} catch (final Exception e) {
			System.err.println("file " + filename + " not found");
			return null;
		}
		return rawBuffer;
	}

	/**
	 * @param args
	 * @throws InterruptedException
	 * @throws IOException
	 * @throws UnknownHostException
	 */
	public static void main(final String[] args) throws InterruptedException, UnknownHostException, IOException {
		System.out.println("Start Load Test with " + Configuration.getInstance().getMaxConnections() + " Threads");
		//System.out.println("Hint: Error messages Broken Pipe means prop that alma did not accept a certain connection");
		long runTime = 0;
		int argInd = 0;
		String filename = null;

		// Iterate over all of the arguments
		for (argInd = 0; argInd < args.length; argInd++) {

			// Break out if argument does not start with '-'
			if (args[argInd].charAt(0) != '-') {
				break;

			} else if (args[argInd].equalsIgnoreCase("-f") || args[argInd].equalsIgnoreCase("-file")) {
				argInd++;
				filename = args[argInd];
				System.out.println("Use raw encoded file: " + filename);

			} else if (args[argInd].equalsIgnoreCase("-h") || args[argInd].equalsIgnoreCase("-hostname")) {
				argInd++;
				Configuration.getInstance().setAlmaHost(args[argInd]);
				System.out.println("Use hostname: " + Configuration.getInstance().getAlmaHost());

			} else if (args[argInd].equals("-p") || args[argInd].equals("-port")) {
				argInd++;
				final String port = args[argInd];
				try {
					Configuration.getInstance().setAlmaPort(Integer.parseInt(port));
					System.out.println("Use port: " + Configuration.getInstance().getAlmaPort());
				} catch (final NullPointerException e) {
					System.err.println("Error: Use digits for the portnumber! Parameter was: " + e.getLocalizedMessage());
				} catch (final NumberFormatException e) {
					System.err.println("Error: Use digits for the portnumber! Parameter was: " + e.getLocalizedMessage());
				}

			} else if (args[argInd].equals("-s") || args[argInd].equals("-sleep")) {
				argInd++;
				final String sleep = args[argInd];
				try {
					Configuration.getInstance().setSleepTime(Integer.parseInt(sleep));
					System.out.println("Use Sleep time between Requests: " + Configuration.getInstance().getSleepTime());
				} catch (final NullPointerException e) {
					System.err.println("Error: Use digits for the Sleep time! Parameter was: " + e.getLocalizedMessage());
				} catch (final NumberFormatException e) {
					System.err.println("Error: Use digits for the Sleep time! Parameter was: " + e.getLocalizedMessage());
				}


			} else {
				System.err.println("Error: unknown argument " + args[argInd]);
				usage();
				System.exit(1);
			}
		}

		if (filename == null || Configuration.getInstance().getAlmaHost() == null || Configuration.getInstance().getAlmaPort() == 0) {
			usage();
			System.exit(1);
		}


		byte[] rawBuffer = null;
		rawBuffer = loadBuffer(filename);
		//setup Database
		if (rawBuffer == null) {
			System.err.println("Error while loading " + filename + " file. Test aborted");
		} else {

			//and does the measuring stuff
			Timer timer = null;
			try {
				timer = new Timer();
				final int count = Configuration.getInstance().getStatsAllMilliseconds();
				timer.schedule(new MinuteTimer(count), count, count);
				System.out.printf("type\t\t\treq\tµsec\n");
				final long start = System.currentTimeMillis();

				//fire up the worker threads:
				execution(rawBuffer);

				//measuring done ...
				runTime = System.currentTimeMillis() - start;
			} catch (final java.net.ConnectException e) {
				System.err.println("Error while connection: Check Cabu and you settings!");
				System.err.println("Error Message: " + e.getLocalizedMessage());
			} finally {
				timer.cancel();
			}
		}

		//Stats
		System.out.println("Runtime was " + runTime + "ms");


	}

	final static void usage() {
		System.out.println("Expected Arguments -p[ort] -h[ostname] -f[filename] -s[leep]");
		System.out.println("");
		System.out.println("For example:");
		System.out.println("java -jar generator-load-alma-1.0.jar -hostname localhost -port 4567 -file lala.raw -sleep 1");

	}
}
