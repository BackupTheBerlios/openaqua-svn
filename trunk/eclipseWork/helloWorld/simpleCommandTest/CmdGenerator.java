package simpleCommandTest;

import openaqua.base.ICommand;
import openaqua.base.IRecord;

public class CmdGenerator implements ICommand {

	public boolean execute(IRecord record) {
		boolean result = false;
		if (record instanceof CRecord) {
			CRecord r = (CRecord) record;
			r.setString("hallo");
			result = true;
		}
		return result;
	}
	
	
}
