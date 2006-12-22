/**
 * 
 */
package bot;

import record.IEvent;
import org.apache.log4j.*;

/**
 * @author tukaram
 *
 */
public class CBot implements IBot {
	private static Logger logger = Logger.getRootLogger();

	public CBot() {
		logger.debug("CBot::CBot");
	}
	
	
	public void registerBot(IBot register) {
		logger.debug("CBot::registerBot");
			
	}
	
	
	public void unregisterBot(IBot register) {
		logger.debug("CBot::unregisterBot");
			
	}
	
	
	public void inputPort(IEvent event) {
		logger.debug("CBot::inputEvent");
			
	}
	
	
	public void outputPort(IEvent event) {
		logger.debug("CBot::outputEvent");
			
	}

}
