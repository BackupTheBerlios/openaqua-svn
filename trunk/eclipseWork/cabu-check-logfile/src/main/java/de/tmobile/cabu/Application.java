/**
 * 
 */
package de.tmobile.cabu;

import java.io.IOException;



/**
 * @author behrenan
 * 
 */
public class Application {
	final private static Logger	logger	= Logger.getRootLogger();


	protected int parseCommandLine(final String[] args) {
		int argInd = 0;
		// Iterate over all of the arguments
		for (argInd = 0; argInd < args.length; argInd++) {

			// Break out if argument does not start with '-'
			if (args[argInd].charAt(0) != '-') {
				break;
			}

			if (args[argInd].equalsIgnoreCase("-h") || args[argInd].equalsIgnoreCase("-help")) {
				return -1;

			} else if (args[argInd].equalsIgnoreCase("-a") || args[argInd].equalsIgnoreCase("-all")) {
				Configuration.getInstance().setShowAll(true);

			} else if (args[argInd].equalsIgnoreCase("-l") || args[argInd].equalsIgnoreCase("-logfile")) {
				argInd++;
				Configuration.getInstance().setLogFile(args[argInd]);

			} else if (args[argInd].equalsIgnoreCase("-t") || args[argInd].equalsIgnoreCase("-type")) {
				argInd++;
				final String type = args[argInd];
				if (type.equals("chc")) {
					Configuration.getInstance().setLogFileType(1);
				} else if (type.equals("xoxi")) {
					Configuration.getInstance().setLogFileType(2);
				} else {
					logger.error("Unknown Type of Logfile, can be xoxi or chc only");
					return -3;
				}

			} else {
				logger.error("unknown argument " + args[argInd]);
				return -2;
			}
		}

		if (Configuration.getInstance().getLogFile() == null) {
			logger.error("Program needs a logFile ");
			return -4;
		}
		if (Configuration.getInstance().getLogFileType() == 0) {
			logger.error("Program needs a Type of Logfile ");
			return -5;
		}

		return 0;
	}


	public int run(final String[] arg) throws IOException {

		// check parameters
		int result = -1;
		try {
			result = parseCommandLine(arg);
		} finally {
			if (result != 0) {
				usage();
				return result;
			}
		}

		// Read Content
		final LogFile logfile = new LogFile(Configuration.getInstance().getLogFile());
		logfile.read();

		// Process Content
		LogFileLineDispatcher.parse(logfile.iterator());

		// Print Results:
		logger.printHeader();
		Statistic.getInstance().print();

		Error6.getInstance().print();
		ErrorNoAlma.getInstance().print();
		ErrorMisc.getInstance().print();
		ErrorChc.getInstance().print();

		logger.empty();
		logger.header();

		return result;
	}


	protected void usage() throws IOException {
		logger.out("\nUsage: ParseLogFile [-h] [-logfile logfile] [-mail mailtargets]\n" + "    -h[elp]\tPrint this usage message and exit\n" + "    -t[type]\tThe Type of logfile, might be \"chc\" or \"xoxi\"\n" + "    -l[logfile]\tParse the given logfile\n" + "    -a[ll]\t show all entries\n" + "    \n");
	}
}
