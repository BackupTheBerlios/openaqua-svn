package openaqua.defaultCommands;

import openaqua.base.CRecord;
import junit.framework.TestCase;

public class CmdUsageCounterTest extends TestCase {
    public CmdUsageCounterTest(String name) {
        super(name);
    }

    /**
     * Calls the execution method with null. Nothing should happen
     *
     */
    public void testResultByNullRecord() {
    	CmdUsageCounter cmdBefore = new CmdUsageCounter();
    	assertTrue(cmdBefore.execute(null));
    }

    
    public void testResultByDefaultRecord() {
    	//
    	CmdUsageCounter cmd = new CmdUsageCounter();
    	CRecord recBefore = new CRecord();
    	CRecord recAfter = (CRecord)recBefore.clone();

    	//compare the record
    	assertTrue(cmd.execute(recBefore ));
    	assertTrue(recBefore.equals(recAfter));
   }

    public void testUsage0() {
    	CmdUsageCounter cmd = new CmdUsageCounter();
    	assertTrue(cmd.getUsage() == 0);
    }

    public void testUsage1() {
    	CmdUsageCounter cmd = new CmdUsageCounter();
    	CRecord rec = new CRecord();
    	cmd.execute(rec);
    	assertTrue(cmd.getUsage() == 1);
    }

    public void testUsage2() {
    	CmdUsageCounter cmd = new CmdUsageCounter();
    	CRecord rec = new CRecord();
    	cmd.execute(rec);
    	cmd.execute(rec);
    	System.err.print(cmd.getUsage());
    	assertTrue(cmd.getUsage() == 2);
    }
  
    public void testClear() {
    	CmdUsageCounter cmd = new CmdUsageCounter();
    	CRecord rec = new CRecord();
    	cmd.execute(rec);
    	cmd.execute(rec);
    	cmd.resetUsage();
    	assertTrue(cmd.getUsage() == 0);
    }
    
}
