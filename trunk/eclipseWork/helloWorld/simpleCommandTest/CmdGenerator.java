package simpleCommandTest;

import openaqua.base.ICommand;
import openaqua.base.IEvent;

public class CmdGenerator implements ICommand {

	public boolean execute(IEvent event) {
		boolean result = false;
		if (event instanceof CRecord) {
			CRecord r = (CRecord) event;
			r.setString("hallo");
			result = true;
		}
		return result;
	}
	
	
}
