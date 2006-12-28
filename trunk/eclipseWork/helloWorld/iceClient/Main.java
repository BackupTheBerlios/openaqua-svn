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
			//Setup a Simple Logger
			PatternLayout layout = new PatternLayout( "%-5p\t[%t] %c: %m%n" );
			
			//Logger for Console
	        ConsoleAppender consoleAppender = new ConsoleAppender( layout );
	        logger.addAppender( consoleAppender );
	        
	        //Logger for File
	        //FileAppender fileAppender = new FileAppender( layout, "MeineLogDatei.log", false );
	        //logger.addAppender( fileAppender );
	        
	        //Set Default Debug Level
	        // ALL | DEBUG | INFO | WARN | ERROR | FATAL | OFF:
	        logger.setLevel( Level.ALL);

	        int status = 0;
	        Ice.Communicator ic = null;
	        try {
	        	ic = Ice.Util.initialize(args);
	        	Ice.ObjectPrx base = ic.stringToProxy("SimplePrinter:default -p 10000");
	        	Demo.PrinterPrx printer = Demo.PrinterPrxHelper.checkedCast(base);
	        	if (printer == null) {
	        		throw new Error ("Invalid Proxy");
	        	}
	        	printer.printString("Hello World");
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
	        //setup and execute the Connector object
	        logger.info("Done");
	        System.exit(status);
	        
		} catch( Exception ex ) {
			ex.printStackTrace();
			System.out.println( ex );
	    }

	}

}
