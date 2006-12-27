package simpleCommandTest;

import openaqua.base.ICommand;
import openaqua.base.IRecord;

public class CmdDumpRecord implements ICommand {
	public boolean execute(IRecord record) {
		boolean result = false;
		if (record instanceof CRecord) {
			CRecord r = (CRecord) record;

			System.out.println("CRecord:\t" + r.getString());
			
			result = true;
		}
		return result;
	}

}
