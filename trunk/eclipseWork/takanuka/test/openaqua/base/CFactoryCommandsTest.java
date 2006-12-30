package openaqua.base;

import org.junit.Test;
import junit.framework.TestCase;


public class CFactoryCommandsTest extends TestCase {

	@Test
	public final void testGetInstance() {
		CFactoryCommands a = CFactoryCommands.getInstance();
		CFactoryCommands b = CFactoryCommands.getInstance();
		assertTrue(a == b);    	
		assertTrue(a != null);
	}

	@Test
	public final void testRegisterBuilder() {
		try {
			CFactoryCommands.getInstance().registerBuilder(null);
			fail("Should throw NullPointerException");
		} catch( NullPointerException e) {
			// its ok
		}


		fail("Not yet implemented"); // TODO
	}

	@Test
	public final void testUnregisterBuilder() {
		fail("Not yet implemented"); // TODO
	}

	@Test
	public final void testGetCommand() {
		fail("Not yet implemented"); // TODO
	}

	@Test
	public final void testCreateCommand() {
		fail("Not yet implemented"); // TODO
	}

	@Test
	public final void testAddCommand() {
		fail("Not yet implemented"); // TODO
	}

	@Test
	public final void testObject() {
		fail("Not yet implemented"); // TODO
	}

	@Test
	public final void testGetClass() {
		fail("Not yet implemented"); // TODO
	}

	@Test
	public final void testHashCode() {
		fail("Not yet implemented"); // TODO
	}

	@Test
	public final void testEquals() {
		fail("Not yet implemented"); // TODO
	}

	@Test
	public final void testClone() {
		fail("Not yet implemented"); // TODO
	}

	@Test
	public final void testToString() {
		fail("Not yet implemented"); // TODO
	}

	@Test
	public final void testNotify() {
		fail("Not yet implemented"); // TODO
	}

	@Test
	public final void testNotifyAll() {
		fail("Not yet implemented"); // TODO
	}

	@Test
	public final void testWaitLong() {
		fail("Not yet implemented"); // TODO
	}

	@Test
	public final void testWaitLongInt() {
		fail("Not yet implemented"); // TODO
	}

	@Test
	public final void testWait() {
		fail("Not yet implemented"); // TODO
	}

	@Test
	public final void testFinalize() {
		fail("Not yet implemented"); // TODO
	}

}
