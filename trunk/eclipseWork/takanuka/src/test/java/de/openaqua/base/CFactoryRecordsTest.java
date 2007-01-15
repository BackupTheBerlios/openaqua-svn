package de.openaqua.base;

import junit.framework.TestCase;


public class CFactoryRecordsTest extends TestCase {


	public void testIsSingleton() {
		CFactoryContexts a = CFactoryContexts.getInstance();
		CFactoryContexts b = CFactoryContexts.getInstance();
		assertTrue(a == b);
		assertTrue(a != null);
	}

	public void testGetRecord() {
		CRecord rec = new CRecord();
		CFactoryContexts.getInstance().addRecordPrototyp(0, rec);
		IContext irec = CFactoryContexts.getInstance().getRecord(0);
		assertTrue(irec != null);
		assertTrue(irec instanceof CRecord);
		assertEquals(rec, irec);
	}

	public void testAddRecordPrototyp() {
		try {
			CFactoryContexts.getInstance().addRecordPrototyp(0, null);
			fail("Should throw NullPointerException");
		} catch( NullPointerException e) {
			// its ok
		}

	}

}
