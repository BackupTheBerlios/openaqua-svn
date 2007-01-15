package openaqua.defaultCommands;

import openaqua.base.CRecord;
import junit.framework.TestCase;

public class CmdDumpRecordTest extends TestCase {
    public CmdDumpRecordTest(String name) {
        super(name);
    }

    /**
     * Calls the execution method with null. Nothing should happen
     *
     */
    public void testResultByNullRecord() {
    	CmdDumpRecord cmdBefore = new CmdDumpRecord();
    	assertTrue(cmdBefore.execute(null));
    }

    
    public void testResultByDefaultRecord() {
    	//
    	CmdDumpRecord cmd = new CmdDumpRecord();
    	CRecord recBefore = new CRecord();
    	CRecord recAfter = (CRecord)recBefore.clone();

    	//compare the record
    	assertTrue(cmd.execute(recBefore ));
    	assertTrue(recBefore.equals(recAfter));
   }


}
