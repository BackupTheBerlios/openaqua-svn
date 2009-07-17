/**
 * 
 */
package de.openaqua.sim.main;


import java.io.PrintWriter;
import java.sql.DriverManager;

import de.openaqua.vwl.CAlmaConnection;
import de.openaqua.vwl.CConfiguration;
import de.openaqua.vwl.TTConnection;


/**
 * @author behrenan
 * 
 */
public class Main {
	/**
	 * @param args
	 * @throws ClassNotFoundException
	 */
	public static void main(final String[] args) {
		String dsnname = null;
		boolean isCSConn = false;
		boolean doTrace = false;
		int whatToRun = 0;
		int argInd = 0;

		// Iterate over all of the arguments
		for (argInd = 0; argInd < args.length; argInd++) {

			// Break out if argument does not start with '-'
			if (args[argInd].charAt(0) != '-') {
				break;
			}

			if (args[argInd].equalsIgnoreCase("-h") || args[argInd].equalsIgnoreCase("-help")) {
				usage();
				System.exit(0);

			} else if (args[argInd].equalsIgnoreCase("-c") || args[argInd].equalsIgnoreCase("-client")) {
				isCSConn = true;

			} else if (args[argInd].equalsIgnoreCase("-t") || args[argInd].equalsIgnoreCase("-trace")) {
				doTrace = true;

			} else if (args[argInd].equals("-r") || args[argInd].equals("-run")) {
				argInd++;
				if (argInd >= args.length) {
					System.err.println("Error: -run option requires an argument");
					usage();
					System.exit(1);
				}

				try {
					whatToRun = Integer.parseInt(args[argInd]);
				} catch (final NumberFormatException ex) {
					System.err.println("Error: -run option requires a number.");
					usage();
					System.exit(1);
				}

			} else if (args[argInd].equalsIgnoreCase("-dsn")) {
				argInd++;
				if (argInd >= args.length) {
					System.err.println("Error: -dsn option requires an argument");
					usage();
					System.exit(1);
				}

				dsnname = args[argInd];

			} else {
				System.err.println("Error: unknown argument " + args[argInd]);
				usage();
				System.exit(1);
			}
		}

		// If there are any left over arguments, treat it as a dsnname;
		if (argInd < args.length) {
			if (dsnname != null) {
				System.err.println("Error: extra argument. Parsing stopped at " + args[argInd]);
				usage();
				System.exit(1);
			}
			dsnname = args[argInd];
			argInd++;
		}

		// If dsnname is not set at this point, it as an error.
		if (dsnname == null || dsnname.length() == 0) {
			System.err.println("Error: dsnname missing.  It is required.");
			usage();
			System.exit(1);
		}

		// If there are any left over arguments, it is an error at this
		// point.
		if (argInd < args.length) {
			System.err.println("Error: too many arguments. Parsing stopped at " + args[argInd]);
			usage();
			System.exit(1);
		}

		// Enable tracing in TimesTen JDBC driver for debugging
		if (doTrace) {
			DriverManager.setLogWriter(new PrintWriter(System.out, true));
		}

	}

	public static void usage() {
		System.err.println("\nUsage: vwl-sim [-h] [-t] [-run num] [-file] filename\n"
				+ "    -h[elp]\tPrint this usage message and exit\n" + "    -t[race]\tTurn on JDBC driver debug tracing\n"
				+ "    -c[lient]\tConnect using client/server (default is direct connect)\n"
				);
	}

}
