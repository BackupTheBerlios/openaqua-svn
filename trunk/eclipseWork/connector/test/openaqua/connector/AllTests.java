package openaqua.connector;

import junit.framework.Test;
import junit.framework.TestSuite;

public class AllTests {

	public static Test suite() {
		junit.framework.JUnit4TestAdapter suite = new junit.framework.JUnit4TestAdapter()
		
		return new junit.framework.JUnit4TestAdapter(ClientRecordTest.class);
		
		//TestSuite suite = new TestSuite("Test for openaqua.defaultCommands");
		//$JUnit-BEGIN$
		//suite.addTestSuite(ClientRecordTest.class);
		//$JUnit-END$
		//return suite;
	}

	public static junit.framework.Test suite2() {
		return new junit.framework.JUnit4TestAdapter(ClientRecordTest.class);
	}
}



