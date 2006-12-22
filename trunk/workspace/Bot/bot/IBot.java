/**
 * 
 */
package bot;

import record.CRecord;

/**
 * @author tukaram
 *
 */
public interface IBot {

	
	/**
	 * Register the Bot somewhere
	 */
	public  void Register();
	
	public void pickupRecord(CRecord record);
}
