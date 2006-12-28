/**
 * 
 */
package iceClient;


import org.apache.log4j.ConsoleAppender;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.apache.log4j.PatternLayout;

/**
 * @author tukaram
 *
 */
public class Main {
	private static Logger logger = Logger.getRootLogger();
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			logger.debug("Client: Startup");
			PatternLayout layout = new PatternLayout( "%-5p\t[%t] %c: %m%n" );
	        ConsoleAppender consoleAppender = new ConsoleAppender( layout );
	        logger.addAppender( consoleAppender );
	        logger.setLevel( Level.ALL);

	        int status = 0;
	        Ice.Communicator ic = null;
	        try {
				logger.debug("Client: Init");
	        	ic = Ice.Util.initialize(args);
	        	Ice.ObjectPrx base = ic.stringToProxy("SimplePrinter:default -p 10000");
	        	Demo.PrinterPrx printer = Demo.PrinterPrxHelper.checkedCast(base);
	        	if (printer == null) {
	        		throw new Error ("Invalid Proxy");
	        	}
				logger.debug("Client: Print");
	        	printer.printString("Hello World");
	        } catch (Ice.LocalException e) {
	        	e.printStackTrace();
	        	status = 1;
	        } catch (Exception e) {
	        	e.printStackTrace();
	        	System.err.println(e.getMessage());
	        	status = 2;
	        }

	        logger.debug("Client: Finish");
	        
	        if (ic != null) {
	        	try {
	        		ic.destroy();
	        	} catch (Exception e) {
		        	e.printStackTrace();
		        	System.err.println(e.getMessage());
		        	status = 3;
	        	}
	        }
	        //setup and execute the Connector object
	        logger.debug("Client: Finished");
	        System.exit(status);
	        
		} catch( Exception ex ) {
			ex.printStackTrace();
			System.out.println( ex );
	    }

	}

}
