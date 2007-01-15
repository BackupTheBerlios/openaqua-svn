package de.openaqua.defaultCommands;

import junit.framework.Test;
import junit.framework.TestSuite;

public class AllTests {

	public static Test suite() {
		TestSuite suite = new TestSuite("Test for openaqua.defaultCommands");
		//$JUnit-BEGIN$
		suite.addTestSuite(CmdDoNothingTest.class);
		suite.addTestSuite(CmdUsageCounterTest.class);
		suite.addTestSuite(CmdDumpRecordTest.class);
		//$JUnit-END$
		return suite;
	}

}
