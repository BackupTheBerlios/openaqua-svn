/**
 * 
 */
package bot;

import record.CRecord;

/**
 * @author tukaram
 *
 */
public class BotRecordCreator implements IBot {
	private static int m_recordCounter = 0;

	/* (non-Javadoc)
	 * @see bot.IBot#Register()
	 */
	public void Register() {
		// TODO Auto-generated method stub

	}

	/**
	 * 
	 *
	 */
	public void offerRecord() {
		CRecord r = new CRecord();
		r.setValue(m_recordCounter ++);
	}
	
	
	public void pickupRecord(CRecord record) {
		// TODO Auto-generated method stub
		
	}

}
