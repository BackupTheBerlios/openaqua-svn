package de.openaqua.dev.entities;

import de.openaqua.dev.entities.Address;
import junit.framework.TestCase;

/**
 * @author behrenan
 *
 */
public class AddressTest extends TestCase {

	/**
	 * @param arg0
	 */
	public AddressTest(String arg0) {
		super(arg0);
	}


	/* (non-Javadoc)
	 * @see junit.framework.TestCase#setUp()
	 */
	protected void setUp() throws Exception {
		super.setUp();
	}

	/* (non-Javadoc)
	 * @see junit.framework.TestCase#tearDown()
	 */
	protected void tearDown() throws Exception {
		super.tearDown();
	}

	
	public final void testGetInstance() {
		Address a = new AddressImpl();
		Address b = new AddressImpl();
		assertNotSame(a, b);
		assertNotNull(b);
		assertNotNull(b);
		
	}
	
	/**
	 * Test method for {@link de.openaqua.dev.entities.Address#hashCode()}.
	 */
	public void testHashCode() {
		Address a = new AddressImpl();
		Address b = new AddressImpl();
		
		assertEquals(0, a.hashCode());
		assertEquals(a.hashCode(), a.hashCode());
		assertEquals(a.hashCode(), b.hashCode());

		assertEquals(0, b.hashCode());
		assertEquals(b.hashCode(), b.hashCode());
		assertEquals(b.hashCode(), a.hashCode());
		
		a.setId(1L);
		assertNotSame(0, a.hashCode());
		assertEquals(a.hashCode(), a.hashCode());
		assertNotSame(a.hashCode(), b.hashCode());

		assertEquals(0, b.hashCode());
		assertEquals(b.hashCode(), b.hashCode());

		b.setId(1L);
		assertNotSame(0, b.hashCode());
		assertEquals(a.hashCode(), b.hashCode());
		assertEquals(b.hashCode(), b.hashCode());
		
		
	}

	/**
	 * Test method for {@link de.openaqua.dev.entities.Address#getStreet()}.
	 */
	public void testGetStreet() {
		Address a = new AddressImpl();
		assertNull(a.getStreet());

		String foo = "foo";
		a.setStreet(foo);
		assertEquals(foo, a.getStreet());

		foo = "foo2";
		a.setStreet(foo);
		assertEquals(foo, a.getStreet());
	}

	/**
	 * Test method for {@link de.openaqua.dev.entities.Address#setStreet(java.lang.String)}.
	 */
	public void testSetStreet() {
		Address a = new AddressImpl();
		assertNull(a.getStreet());
		String foo = "foo";
		a.setStreet(foo);
		assertEquals(foo, a.getStreet());
	}

	/**
	 * Test method for {@link de.openaqua.dev.entities.Address#getTypeOfAddress()}.
	 */
	public void testGetTypeOfAddress() {
		//fail("Not yet implemented");
	}

	/**
	 * Test method for {@link de.openaqua.dev.entities.Address#setTypeOfAddress(de.openaqua.dev.entities.TypeOfAddress)}.
	 */
	public void testSetTypeOfAddress() {
		//fail("Not yet implemented");
	}

	/**
	 * Test method for {@link de.openaqua.dev.entities.Address#getId()}.
	 */
	public void testGetId() {
		Address a = new AddressImpl();
		assertNull(a.getId());
	}

	/**
	 * Test method for {@link de.openaqua.dev.entities.Address#setId(java.lang.Long)}.
	 */
	public void testSetId() {
		Address a = new AddressImpl();
		java.lang.Long id = 1L;

		assertNull(a.getId());

		a.setId(id);
		assertEquals(a.getId(), id);
	}

	/**
	 * Test method for {@link de.openaqua.dev.entities.Address#getCity()}.
	 */
	public void testGetCity() {
		Address a = new AddressImpl();
		assertNull(a.getCity());
	}

	/**
	 * Test method for {@link de.openaqua.dev.entities.Address#setCity(de.openaqua.dev.entities.City)}.
	 */
	public void testSetCity() {
		//fail("Not yet implemented");
	}

	/**
	 * Test method for {@link de.openaqua.dev.entities.Address#equals(java.lang.Object)}.
	 */
	public void testEqualsObject() {
		Address a = new AddressImpl();
		Address b = new AddressImpl();
		
		assertTrue(a.equals(a));
		assertTrue(b.equals(b));
		
		a.setId(1L);
		b.setId(1L);
		
		assertTrue(a.equals(b));
		assertTrue(b.equals(a));
		
		b.setId(2L);

		assertFalse(a.equals(b));
		assertFalse(b.equals(a));

		assertTrue(a.equals(a));
		assertTrue(b.equals(b));
		
	}

}
