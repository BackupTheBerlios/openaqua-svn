package openaqua.defaultCommands;

import openaqua.base.CRecord;
import junit.framework.TestCase;

public class CmdDoNothingTest extends TestCase {

    public CmdDoNothingTest(String name) {
        super(name);
    }

    protected void setUp() {
    	//
    }

    protected void tearDown() {
        // beenden von Netzwerk- oder Datenbankverbindungen
    }
    
    public void testResultByNullRecord() {
    	//well, this would need a record, but the constructor is private. :(
    	CmdDoNothing cmdBefore = new CmdDoNothing();
    	assertTrue(cmdBefore.execute(null));
    }

    
    public void testResultByDefaultRecord() {
    	//well, this would need a record, but the constructor is private. :(
    	CmdDoNothing cmd = new CmdDoNothing();
    	CRecord recBefore = new CRecord();
    	CRecord recAfter = (CRecord)recBefore.clone();

    	//compare the record
    	assertTrue(cmd.execute(recBefore ));
    	assertTrue(recBefore.equals(recAfter));
   }

}
