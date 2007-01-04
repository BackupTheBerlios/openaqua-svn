package simpleCommandTest;

import openaqua.base.ICommand;
import openaqua.base.IContext;

public class CmdDumpRecord implements ICommand {
	public boolean execute(IContext context) {
		boolean result = false;
		if (context instanceof CRecord) {
			CRecord r = (CRecord) context;

			System.out.println("CRecord:\t" + r.getString());
			
			result = true;
		}
		return result;
	}

}
