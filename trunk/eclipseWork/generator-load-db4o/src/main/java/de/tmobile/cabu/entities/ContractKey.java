/**
 * 
 */
package de.tmobile.cabu.entities;



import com.db4o.config.annotations.Indexed;
/**
 * @author behrenan
 *
 */
public class ContractKey {
	@Indexed
	public int key;

	public ContractKey(int key)         { 
		this.key = key;
	}
	
	/**
	 * @return the key
	 */
	public int getKey() {
		return key;
	}
}
