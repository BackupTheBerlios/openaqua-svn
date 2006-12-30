package openaqua.defaultCommands;

import openaqua.base.CRecord;
import junit.framework.TestCase;

public class CmdDoNothingTest extends TestCase {
	private CmdDoNothing cmd = new CmdDoNothing();
	//private CRecord rec = new CRecord();

    public CmdDoNothingTest(String name) {
        super(name);
    }

    protected void setUp() {
    	cmd = new CmdDoNothing();
    }

    protected void tearDown() {
        // beenden von Netzwerk- oder Datenbankverbindungen
    }
    
    public void testResultByNullRecord() {
    	//well, this would need a record, but the constructor is private. :(
    	assertTrue(cmd.execute(null));
    }

//    public void testAmount() {
//        assertTrue(2.00 == two.getAmount());
//    }
//
//    public void testRounding() {
//        Euro roundedTwo = new Euro(1.995);
//        assertEquals("rounded amount",
//            2.00, roundedTwo.getAmount(), 0.001);
//    }
//
//    public void testAdding() {
//        Euro three = two.add(new Euro(1.00));
//        assertEquals("sum", 3.00, three.getAmount(), 0.001);
//        assertEquals("two", 2.00, two.getAmount(), 0.001);
//    }
//
//    public static Test suite() {
//        return new TestSuite(EuroTest.class);
//    }
//
//    public static void main(String[] args) {
//        junit.swingui.TestRunner.run(EuroTest.class);
//    }

}
