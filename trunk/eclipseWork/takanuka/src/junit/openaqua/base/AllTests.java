package openaqua.base;

import junit.framework.Test;
import junit.framework.TestSuite;

public class AllTests {

	public static Test suite() {
		TestSuite suite = new TestSuite("Test for openaqua.base");
		//$JUnit-BEGIN$
		suite.addTestSuite(CFactoryRecordsTest.class);
		suite.addTestSuite(CFactoryCommandsTest.class);
		//$JUnit-END$
		return suite;
	}

}
