package openaqua.defaultCommands;


import org.apache.log4j.Logger;
import openaqua.base.ICommand;
import openaqua.base.IEvent;



public class CmdDumpRecord implements ICommand {
	private static Logger logger = Logger.getRootLogger();

	/**
	 * takes an IRecord and dumps it to Log4j.info
	 * 
	 * @return true - whatever happens
	 */
	public boolean execute(IEvent event) {
		if (event != null) {
			logger.info(event.toString());
		} else {
			logger.info("IRecord is null");
		}
		return true;
	}

}
