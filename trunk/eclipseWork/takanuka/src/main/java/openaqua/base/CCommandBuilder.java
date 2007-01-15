package openaqua.base;

import openaqua.defaultCommands.CmdDoNothing;
import openaqua.defaultCommands.CmdDumpRecord;
import openaqua.defaultCommands.CmdUsageCounter;

public class CCommandBuilder implements ICommandBuilder{

	public ICommand createCommand(int id) {
		if (id == 0) return new CmdDoNothing();
		if (id == 1) return new CmdDumpRecord();
		if (id == 2) return new CmdUsageCounter();
		return null;
	}

}
