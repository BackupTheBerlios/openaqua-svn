/**
 * 
 */
package de.openaqua.vwl.sim;

import org.apache.log4j.ConsoleAppender;
import org.apache.log4j.Level;
import org.apache.log4j.PatternLayout;

import org.apache.log4j.Logger;



/**
 * @author behrenan
 * 
 */
public class Main {
	private static Logger logger = Logger.getRootLogger();
	private static Level defaultLevel = Level.ALL;
	
	
	/**
	 * Setup a the Logger output 
	 * @param l The root logger
	 */
	private static void setupLogger(final Logger l){
		PatternLayout layout = new PatternLayout( "%-5p [%t] %C{1} -> %m%n" );
        ConsoleAppender consoleAppender = new ConsoleAppender( layout );
        l.addAppender( consoleAppender );
        l.setLevel( defaultLevel );
	}

	private static void parseCommandLineArgs(final String[] args,  String filename ){
		
		// Iterate over all of the arguments
		int argInd = 0;
		for (; argInd < args.length; argInd++) {

			// Break out if argument does not start with '-'
			if (args[argInd].charAt(0) != '-') {
				break;
			}

			if (args[argInd].equalsIgnoreCase("-h") || args[argInd].equalsIgnoreCase("-help")) {
				usage();
				System.exit(0);

			} else if (args[argInd].equals("-f") || args[argInd].equals("-file")) {
				argInd++;
				if (argInd >= args.length) {
					logger.error("Error: -file option requires an argument");
					usage();
					System.exit(1);
				}

				filename = args[argInd];


			} else {
				logger.error("Error: unknown argument " + args[argInd]);
				usage();
				System.exit(1);
			}
		}

		if (argInd <= args.length) {
			if (filename == null){
				System.err.println();
				logger.error("Filename missing.");

			}
		}

		// If there are any left over arguments, it is an error at this
		// point.
		if (argInd < args.length) {
			logger.error("Error: too many arguments. Parsing stopped at " + args[argInd]);
			usage();
			System.exit(1);
		}	
		
	}
	

	/**
	 * This is the start point
	 * 
	 * @param args command line arguments
	 */
	public static void main(final String[] args) {
		try {
			setupLogger(logger); //Setup a Simple Logger

			
			//The model will be in ...
			String filename = null;
			parseCommandLineArgs(args, filename);

			
	        //execute the main object
	        logger.info("Done");

		} catch( Exception ex ) {
			ex.printStackTrace();
			System.out.println( ex );
	    }
	
		


	}

	public static void usage() {
		System.err.println("\nUsage: vwl-sim [-h] [-t] [-run num] [-file filename]\n"
				+ "    -h[elp]\tPrint this usage message and exit\n" + "    -t[race]\tTurn on JDBC driver debug tracing\n"
				+ "    -c[lient]\tConnect using client/server (default is direct connect)\n"
				);
	}

}
