package de.openaqua.base;

import de.openaqua.defaultCommands.CmdDoNothing;
import de.openaqua.defaultCommands.CmdDumpRecord;
import de.openaqua.defaultCommands.CmdUsageCounter;

public class CCommandBuilder implements ICommandBuilder{

	public ICommand createCommand(int id) {
		if (id == 0) return new CmdDoNothing();
		if (id == 1) return new CmdDumpRecord();
		if (id == 2) return new CmdUsageCounter();
		return null;
	}

}
