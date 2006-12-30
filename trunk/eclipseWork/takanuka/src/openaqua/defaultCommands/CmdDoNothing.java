package openaqua.defaultCommands;

import org.apache.log4j.Logger;

import openaqua.base.ICommand;
import openaqua.base.IRecord;

public class CmdDoNothing implements ICommand {
	private static Logger logger = Logger.getRootLogger();

	public boolean execute(IRecord record) {
		logger.debug("DoNothing.execute called");
		return true;
	}

}
