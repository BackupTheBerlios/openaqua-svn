package openaqua.defaultCommands;

import openaqua.base.ICommand;
import openaqua.base.IContext;

public class CmdDoNothing implements ICommand {


	public boolean execute(IContext context) {
		return true;
	}

}
