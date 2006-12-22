/**
 * 
 */
package bot;

import org.apache.log4j.Logger;
import record.IEvent;

/**
 * @author tukaram
 *
 */
public class BotRecordCreator extends CBot {
	private static Logger logger = Logger.getRootLogger();

	public  BotRecordCreator() {
		logger.debug("BotRecordCreator::BotRecordCreator");
			
	}

	
	public void registerBot(IBot register) {
		logger.debug("BotRecordCreator::registerBot");
	}

	
	public void unregisterBot(IBot register) {
		logger.debug("BotRecordCreator::unregisterBot");
	}

	
	
	public void inputPort(IEvent event) {
		logger.debug("BotRecordCreator::inputEvent");
	}

	
	public void outputPort(IEvent event) {
		logger.debug("BotRecordCreator::outputEvent");
			
	}
}
