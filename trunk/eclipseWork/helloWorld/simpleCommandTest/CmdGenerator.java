package simpleCommandTest;

import openaqua.base.ICommand;
import openaqua.base.IContext;

public class CmdGenerator implements ICommand {

	public boolean execute(IContext context) {
		boolean result = false;
		if (context instanceof CRecord) {
			CRecord r = (CRecord) context;
			r.setString("hallo");
			result = true;
		}
		return result;
	}
	
	
}
