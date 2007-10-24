/**
 * 
 */
package de.tmobile.xoxi;


import java.io.IOException;
 




/**
 * @author behrenan
 *
 */
public class Application {
	final private static Logger logger = Logger.getRootLogger();

	public int run(final String[] arg) throws IOException {
		int result = 0;
		
		//check parameters
		try {
			result = parseCommandLine(arg);
		} catch (Exception e) {
			result = -1;
		}
		if (result != 0) {
			usage();
			return result;
		}
		
		logger.printHeader();
		
		//Read Content
		LogFile logfile = new LogFile(Configuration.getInstance().getLogFile());
		logfile.read();
		
		
		//Process Content
		LogFileLineDispatcher.parse(logfile.iterator());

		
		//Print Results:
		Logger.getRootLogger().header();
		
		Error6.getInstance().print();
		ErrorNoAlma.getInstance().print();
		ErrorMisc.getInstance().print();
		Statistic.getInstance().print();
		
		
		logger.empty();
		logger.header();



		return result;
	}
	
	
	protected void usage() throws IOException {
		logger.out( "\nUsage: ParseLogFile [-h] [-logfile logfile] [-mail mailtargets]\n"
				+ "    -h[elp]\tPrint this usage message and exit\n"
				+ "    -l[logfile]\tParse the given logfile"
				+ "    \n");
		
		
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

			} else {
				logger.error("unknown argument " + args[argInd]);
				return -2;
			}
		}
		
		if (Configuration.getInstance().getLogFile()==null) {
			logger.error("Program needs a logFile ");
			return -3;
		}
		
		return 0;
	}
	
}
