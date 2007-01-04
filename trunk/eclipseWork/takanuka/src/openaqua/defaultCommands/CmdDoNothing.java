package openaqua.defaultCommands;

import openaqua.base.ICommand;
import openaqua.base.IEvent;

public class CmdDoNothing implements ICommand {


	public boolean execute(IEvent event) {
		return true;
	}

}
