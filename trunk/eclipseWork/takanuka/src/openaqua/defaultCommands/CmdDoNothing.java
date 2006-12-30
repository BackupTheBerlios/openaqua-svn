package openaqua.defaultCommands;

import openaqua.base.ICommand;
import openaqua.base.IRecord;

public class CmdDoNothing implements ICommand {


	public boolean execute(IRecord record) {
		return true;
	}

}
