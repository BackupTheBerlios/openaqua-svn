/**
 * 
 */
package iceServer;

import org.apache.log4j.ConsoleAppender;
import org.apache.log4j.PatternLayout;
import org.apache.log4j.Logger;
import org.apache.log4j.Level;



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
			PatternLayout layout = new PatternLayout( "%-5p\t[%t] %c: %m%n" );
			ConsoleAppender consoleAppender = new ConsoleAppender( layout );
			logger.addAppender( consoleAppender );
	        logger.setLevel( Level.ALL);

	        
	        logger.info("Server: Startup");
	        int status = 0;
	        Ice.Communicator ic = null;
	        try {
		        logger.info("Server: Init");
	        	ic = Ice.Util.initialize(args);
	        	Ice.ObjectAdapter adapter = ic.createObjectAdapterWithEndpoints("SimplePrinterAdapter", "default -p 10000");
	        	Ice.Object object = new PrinterI();
	        	adapter.add(object, Ice.Util.stringToIdentity("SimplePrinter"));
		        logger.info("Server: Activate");
	        	adapter.activate();
		        logger.info("Server: WaitForShutdown");
	        	ic.waitForShutdown();
		        logger.info("Server: Shutdown");
	        } catch (Ice.LocalException e) {
	        	e.printStackTrace();
	        	status = 1;
	        } catch (Exception e) {
	        	e.printStackTrace();
	        	System.err.println(e.getMessage());
	        	status = 2;
	        }
	        
	        if (ic != null) {
	        	try {
	        		ic.destroy();
	        	} catch (Exception e) {
		        	e.printStackTrace();
		        	System.err.println(e.getMessage());
		        	status = 3;
	        	}
	        }
	        logger.info("Server: Finished");
	        System.exit(status);
	        
		} catch( Exception ex ) {
			ex.printStackTrace();
			System.out.println( ex );
	    }

	}

}
