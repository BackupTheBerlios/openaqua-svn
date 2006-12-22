/**
 * 
 */
package bot;

import record.CRecord;
import org.apache.log4j.*;

/**
 * @author tukaram
 *
 */
public class CBot implements IBot {
	  private static Logger logger = Logger.getRootLogger();

	
	  public int getValue(){
		  logger.debug( "getValue" );
		  return 100;
	  }

	  public void pickupRecord(CRecord record) {
		  logger.debug( "pickupRecord" );
	  };

	public void takeRecord(CRecord record) {
		System.out.println("Taken record: " + record.getString());
		
	}
	
	public void Register() {
		// TODO Auto-generated method stub

	}

}
