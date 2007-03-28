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

	@test
	public final void testGetInstance() {
		Address a = new Address();
		Address b = new Address();
		assertNotSame(a, b);
		assertNull(a);
		assertNull(b)
		
	}
	
	/**
	 * Test method for {@link de.openaqua.dev.entities.Address#hashCode()}.
	 */
	public void testHashCode() {
		//fail("Not yet implemented");
	}

	/**
	 * Test method for {@link de.openaqua.dev.entities.Address#getStreet()}.
	 */
	public void testGetStreet() {
		Address a = new Address();
		//fail("Not yet implemented");
	}

	/**
	 * Test method for {@link de.openaqua.dev.entities.Address#setStreet(java.lang.String)}.
	 */
	public void testSetStreet() {
		//fail("Not yet implemented");
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
		//fail("Not yet implemented");
	}

	/**
	 * Test method for {@link de.openaqua.dev.entities.Address#setId(java.lang.Long)}.
	 */
	public void testSetId() {
		//fail("Not yet implemented");
	}

	/**
	 * Test method for {@link de.openaqua.dev.entities.Address#getCity()}.
	 */
	public void testGetCity() {
		//fail("Not yet implemented");
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
		//fail("Not yet implemented");
	}

}
