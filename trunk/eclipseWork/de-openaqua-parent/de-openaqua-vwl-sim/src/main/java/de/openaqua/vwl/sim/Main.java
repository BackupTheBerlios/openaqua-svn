/**
 * 
 */
package de.openaqua.vwl.sim;



/**
 * @author behrenan
 * 
 */
public class Main {

	public static void main(final String[] args) {
		String filename = null;

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
					System.err.println("Error: -file option requires an argument");
					usage();
					System.exit(1);
				}

				filename = args[argInd];


			} else {
				System.err.println("Error: unknown argument " + args[argInd]);
				usage();
				System.exit(1);
			}
		}

		if (argInd < args.length) {
			if (filename == null){
				System.err.println("Error: Filename missing.");
			}
		}

		// If there are any left over arguments, it is an error at this
		// point.
		if (argInd < args.length) {
			System.err.println("Error: too many arguments. Parsing stopped at " + args[argInd]);
			usage();
			System.exit(1);
		}
	}

	public static void usage() {
		System.err.println("\nUsage: vwl-sim [-h] [-t] [-run num] [-file] filename\n"
				+ "    -h[elp]\tPrint this usage message and exit\n" + "    -t[race]\tTurn on JDBC driver debug tracing\n"
				+ "    -c[lient]\tConnect using client/server (default is direct connect)\n"
				);
	}

}
