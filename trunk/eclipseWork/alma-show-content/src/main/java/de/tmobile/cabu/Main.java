/**
 * 
 */
package de.tmobile.cabu;

import java.io.PrintWriter;
import java.sql.DriverManager;

/**
 * @author behrenan
 * 
 */
public class Main {
	static TTConnection mainConnection = null;

	final private static Logger logger = Logger.getRootLogger();

	/**
	 * The name of the TimesTen JDBC Driver (direct connection)
	 */
	private static final String DIRECT_DRIVER = "com.timesten.jdbc.TimesTenDriver";

	/**
	 * The connection prefix of the TimesTen JDBC Driver (direct connection)
	 */
	private static final String DIRECT_CONNECT_PREFIX = "jdbc:timesten:direct:";

	/**
	 * The name of the TimesTen JDBC Driver (client connection)
	 */
	private static final String CLIENT_DRIVER = "com.timesten.jdbc.TimesTenClientDriver";

	/**
	 * The connection prefix of the TimesTen JDBC Driver (client connection)
	 */
	private static final String CLIENT_CONNECT_PREFIX = "jdbc:timesten:client:";

	/**
	 * @param args
	 * @throws ClassNotFoundException
	 */
	public static void main(String[] args) {
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

			if (args[argInd].equalsIgnoreCase("-h")
					|| args[argInd].equalsIgnoreCase("-help")) {
				usage();
				System.exit(0);

			} else if (args[argInd].equalsIgnoreCase("-c")
					|| args[argInd].equalsIgnoreCase("-client")) {
				isCSConn = true;

			} else if (args[argInd].equalsIgnoreCase("-t")
					|| args[argInd].equalsIgnoreCase("-trace")) {
				doTrace = true;

			} else if (args[argInd].equals("-r") || args[argInd].equals("-run")) {
				argInd++;
				if (argInd >= args.length) {
					System.err
							.println("Error: -run option requires an argument");
					usage();
					System.exit(1);
				}

				try {
					whatToRun = Integer.parseInt(args[argInd]);
				} catch (NumberFormatException ex) {
					System.err.println("Error: -run option requires a number.");
					usage();
					System.exit(1);
				}

				if (whatToRun < 0 || whatToRun > 6) {
					System.err
							.println("Error: -run option requires a number between 1 and 6");
					usage();
					System.exit(1);
				}

			} else if (args[argInd].equalsIgnoreCase("-dsn")) {
				argInd++;
				if (argInd >= args.length) {
					System.err
							.println("Error: -dsn option requires an argument");
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
				System.err.println("Error: extra argument. Parsing stopped at "
						+ args[argInd]);
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

		// If there are any left over arguments, it is an error at this point.
		if (argInd < args.length) {
			System.err.println("Error: too many arguments. Parsing stopped at "
					+ args[argInd]);
			usage();
			System.exit(1);
		}

		// Enable tracing in TimesTen JDBC driver for debugging
		if (doTrace) {
			DriverManager.setLogWriter(new PrintWriter(System.out, true));
		}

		// Construct the example-running object
		try {
			AlmaConnection alma;
			if (isCSConn) {
				alma = new AlmaConnection(CLIENT_DRIVER);
				alma.Connect(CLIENT_CONNECT_PREFIX + dsnname);
				alma.listTemplates();
				alma.Disconnect();
			} else {
				alma = new AlmaConnection(DIRECT_DRIVER);
				alma.Connect(DIRECT_CONNECT_PREFIX + dsnname);
				alma.listTemplates();
				alma.Disconnect();
			}
		} catch (ClassNotFoundException e) {
			logger.error("Class Not Found while loading driver ..");
			e.printStackTrace();
		}
	}

	public static void usage() {
		System.err
				.println("\nUsage: AlmaTest [-h] [-t] [-c] [-run num] [-dsn] dsnname\n"
						+ "    -h[elp]\tPrint this usage message and exit\n"
						+ "    -t[race]\tTurn on JDBC driver debug tracing\n"
						+ "    -c[lient]\tConnect using client/server (default is direct connect)\n"
						+ "    -run num\tExample number to run (Default is run all)\n"
						+ "    -dsn\tName of the data store to connect to (required)\n"
						+ "\n    Example number values:\n"
						+ "    1    Loads appropriate driver for the connection type\n"
						+ "    2    Connects to and disconnect from specified data store\n"
						+ "    3    Shows operations performed by a typical application\n"
						+ "    4    Shows how to checkpoint a data store\n"
						+ "    5    Shows how to change and print a query plan\n"
						+ "    6    Shows how to use the batch update facility\n"
						+ "\n\tExample command lines:\n"
						+ "    java -jar alma-show-content-1.0.jar pALMAa\n"
						+ "    java -jar alma-show-content-1.0.jar -run 2 pALMAa\n"
						+ "    java -jar alma-show-content-1.0.jar -client -run 2 -dsn RunDataCS");
	}

}
