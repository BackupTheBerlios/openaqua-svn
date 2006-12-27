/**
 * 
 */
package loggerTest;

import org.apache.log4j.*;

/**
 * @author tukaram
 *
 */
public class LoggerTest {

	  private static Logger logger = Logger.getRootLogger();

		/**
		 * @category main function
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
		        logger.setLevel( Level.ALL );
			} catch( Exception ex ) {
				System.out.println( ex );
		    }
		    
			//A Couple of Sample Output
			logger.debug( "Meine Debug-Meldung" );
		    logger.info(  "Meine Info-Meldung"  );
		    logger.warn(  "Meine Warn-Meldung"  );
		    logger.error( "Meine Error-Meldung" );
		    logger.fatal( "Meine Fatal-Meldung" );
		    
		    
		    //BotRecordCreator bot = new BotRecordCreator();
		    //CEvent ev = new CEvent();
		    //bot.outputPort(ev);
		    //System.out.println(bot.getValue());
		}

}
