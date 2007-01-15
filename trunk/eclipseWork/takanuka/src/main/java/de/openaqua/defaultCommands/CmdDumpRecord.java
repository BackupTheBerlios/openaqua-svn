package de.openaqua.defaultCommands;


import org.apache.log4j.Logger;
import de.openaqua.base.ICommand;
import de.openaqua.base.IContext;



public class CmdDumpRecord implements ICommand {
	private static Logger logger = Logger.getRootLogger();

	/**
	 * takes an IRecord and dumps it to Log4j.info
	 *
	 * @return true - whatever happens
	 */
	public boolean execute(IContext context) {
		if (context != null) {
			logger.info(context.toString());
		} else {
			logger.info("IRecord is null");
		}
		return true;
	}

}
