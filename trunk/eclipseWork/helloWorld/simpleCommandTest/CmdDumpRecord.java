package simpleCommandTest;

import openaqua.base.ICommand;
import openaqua.base.IEvent;

public class CmdDumpRecord implements ICommand {
	public boolean execute(IEvent event) {
		boolean result = false;
		if (event instanceof CRecord) {
			CRecord r = (CRecord) event;

			System.out.println("CRecord:\t" + r.getString());
			
			result = true;
		}
		return result;
	}

}
