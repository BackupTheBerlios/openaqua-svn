package helloWorld;

import junit.framework.TestCase;

public class MainTest extends TestCase {
		private Main myCase;


	     /**
	      * Sets up the test fixture. 
	      * (Called before every test case method.) 
	      */ 
	     protected void setUp() {
	    	 myCase = new Main();
	     } 

	     /**
	      * Tears down the test fixture. 
	      * (Called after every test case method.) 
	      */ 
	     protected void tearDown() {
	    	 //
	     } 


	     public void testGetInt() {
	    	 assertEquals(100, myCase.g100());
	     } 

}
