/**
 * 
 */
package simpleCommandTest;

import org.apache.log4j.*;
import openaqua.base.*;

/**
 * @author tukaram
 *
 */
public class Main {

	  private static Logger logger = Logger.getRootLogger();

		/**
		 * @category main function
		 * @param args
		 */
		
		public static void main(String[] args) {
			try {
				//setup Logger
				PatternLayout layout = new PatternLayout( "%-5p\t[%t] %c: %m%n" );
		        ConsoleAppender consoleAppender = new ConsoleAppender( layout );
		        logger.addAppender( consoleAppender );
		        logger.setLevel( Level.ALL );
		        
		        //Try a simple Macro Execution
		        CMacro m = new CMacro();
		        m.addCommand(new CmdGenerator());
		        m.addCommand(new CmdDumpRecord());

		        CMacro n = new CMacro();
		        n.addCommand(new CmdDumpRecord());
		        m.addCommand(n);
		        
		        m.execute(new CRecord());
		        
		        
			} catch( Exception ex ) {
				System.out.println( ex );
		    }
		    
		}

}
