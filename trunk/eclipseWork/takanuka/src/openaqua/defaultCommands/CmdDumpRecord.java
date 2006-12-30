package openaqua.defaultCommands;


import org.apache.log4j.Logger;
import openaqua.base.ICommand;
import openaqua.base.IRecord;



public class CmdDumpRecord implements ICommand {
	private static Logger logger = Logger.getRootLogger();

	public boolean execute(IRecord record) {
		logger.info(record.toString());
		return false;
	}

}
