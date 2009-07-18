package de.openaqua.base;

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


	}

	@Test
	public final void testUnregisterBuilder() {
		;
	}

	@Test
	public final void testGetCommand() {
		;
	}

	@Test
	public final void testCreateCommand() {
		;
	}

	@Test
	public final void testAddCommand() {
		;
	}

	@Test
	public final void testObject() {
		;
	}

	@Test
	public final void testGetClass() {
		;
	}

	@Test
	public final void testHashCode() {
		;
	}

	@Test
	public final void testEquals() {
		;
	}

	@Test
	public final void testClone() {
		;
	}

	@Test
	public final void testToString() {
		;
	}

	@Test
	public final void testNotify() {
		;
	}

	@Test
	public final void testNotifyAll() {
		;
	}

	@Test
	public final void testWaitLong() {
		;
	}

	@Test
	public final void testWaitLongInt() {
		;
	}

	@Test
	public final void testWait() {
		;
	}

	@Test
	public final void testFinalize() {
		;
	}

}
