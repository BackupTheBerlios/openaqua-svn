package openaqua.base;

import junit.framework.TestCase;


public class CFactoryRecordsTest extends TestCase {


	public void testIsSingleton() {
		CFactoryRecords a = CFactoryRecords.getInstance();
		CFactoryRecords b = CFactoryRecords.getInstance();
		assertTrue(a == b);    	
		assertTrue(a != null);
	}

	public void testGetRecord() {
		CRecord rec = new CRecord();
		CFactoryRecords.getInstance().addRecordPrototyp(0, rec);
		IRecord irec = CFactoryRecords.getInstance().getRecord(0);
		assertTrue(irec != null);
		assertTrue(irec instanceof CRecord);
		assertEquals(rec, irec);
	}
	
	public void testAddRecordPrototyp() {
		try {
			CFactoryRecords.getInstance().addRecordPrototyp(0, null);
			fail("Should throw NullPointerException");
		} catch( NullPointerException e) {
			// its ok
		}
		
	}
	
}
