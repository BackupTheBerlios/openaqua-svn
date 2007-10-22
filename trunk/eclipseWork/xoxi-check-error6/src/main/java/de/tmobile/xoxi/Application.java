/**
 * 
 */
package de.tmobile.xoxi;

import java.io.FileNotFoundException;


/**
 * @author behrenan
 *
 */
public class Application {
	final private static Logger logger = Logger.getRootLogger();

	public Application() {
		logger.debug("Application::Application");
		
	}
	
	public int run(final String[] arg) throws FileNotFoundException {
		int result = 0;
		
		//check parameters
		result = parseCommandLine(arg);
		if (result != 0) {
			usage();
			return result;
		}
		logger.debug("Check file " + Configuration.getInstance().getLogFile());
		
		//Read Content
		LogFile logfile = new LogFile(Configuration.getInstance().getLogFile());
		
		//Process Content
		LogFileLineDispatcher.parse(logfile.iterator());

		
		//Print Results:
		Logger.getRootLogger().info("Average: "+Statistic.getInstance().getAverageTime());
		Logger.getRootLogger().info("Stat Lines: "+Statistic.getInstance().getReadStatLines());
		return result;
	}
	
	
	protected void usage() {
		logger.out( "\nUsage: AlmaTest [-h] [-t] [-c] [-run num] [-dsn] dsnname\n"
				+ "    -h[elp]\tPrint this usage message and exit\n"
				+ "    -t[race]\tTurn on JDBC driver debug tracing\n"
				+ "    -c[lient]\tConnect using client/server (default is direct connect)\n"
				+ "    -run num\tExample number to run (Default is run all)\n"
				+ "    -dsn\tName of the data store to connect to (required)\n"
				+ "\n    Example number values:\n"
				+ "    1    Element SubType\n"
				+ "    2    Care Descriptions\n"
				+ "    3    Type Descriptions\n"
				+ "    4    Contracts (MSISDN+Contract)\n"
				+ "    5    Tempalte Identifications\n"
				+ "    6    Element Ident Assocs\n"
				+ "\n\tExample command lines:\n"
				+ "    java -jar alma-show-content-1.0.jar pALMAa\n"
				+ "    java -jar alma-show-content-1.0.jar -run 2 pALMAa\n"
				+ "    java -jar alma-show-content-1.0.jar -client -run 2 -dsn RunDataCS");
		
		
	}
	
	
	
	
	protected int parseCommandLine(final String[] args) {
		int argInd = 0;
		// Iterate over all of the arguments
		for (argInd = 0; argInd < args.length; argInd++) {

			// Break out if argument does not start with '-'
			if (args[argInd].charAt(0) != '-') {
				break;
			}

			if (args[argInd].equalsIgnoreCase("-h")
					|| args[argInd].equalsIgnoreCase("-help")) {
				return -1;

			} else if (args[argInd].equalsIgnoreCase("-l")
					|| args[argInd].equalsIgnoreCase("-logfile")) {
				argInd++;
				Configuration.getInstance().setLogFile(args[argInd]);

			} else if (args[argInd].equalsIgnoreCase("-m")
					|| args[argInd].equalsIgnoreCase("-mail")) {
				argInd++;
				Configuration.getInstance().setMailToFile(args[argInd]);


			} else {
				logger.error("unknown argument " + args[argInd]);
				return -2;
			}
		}
		
		if (Configuration.getInstance().getLogFile()==null) {
			logger.error("Program needs a logFile directory");
			return -3;
		}
		
		return 0;
	}
	
}
