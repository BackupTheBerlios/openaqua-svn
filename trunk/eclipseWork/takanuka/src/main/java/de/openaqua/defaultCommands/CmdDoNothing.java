package de.openaqua.defaultCommands;

import de.openaqua.base.ICommand;
import de.openaqua.base.IContext;

public class CmdDoNothing implements ICommand {


	public boolean execute(IContext context) {
		return true;
	}

}
