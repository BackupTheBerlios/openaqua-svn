package de.openaqua.dev.entities;

import junit.framework.Test;
import junit.framework.TestSuite;


public class AllTests {

	public static Test suite() {
		TestSuite suite = new TestSuite("Test for default package");
		suite.addTest(AddressTest.class);
		
		//$JUnit-BEGIN$

		//$JUnit-END$
		return suite;
	}

}
