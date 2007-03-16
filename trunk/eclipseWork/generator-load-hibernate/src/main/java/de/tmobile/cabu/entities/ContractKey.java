/**
 * 
 */
package de.tmobile.cabu.entities;



/**
 * @author behrenan
 *
 */
public class ContractKey {
	
	private Integer key;
	private String sss;
	
	public ContractKey()         {
		super();
	}
	
	
	public ContractKey(Integer key)         {
		super();
		this.key = key;
	}
	
	/**
	 * @return the key
	 */
	public Integer getKey() {
		return key;
	}

	public void setKey(Integer key) {
		this.key = key;
	}


	public String getSss() {
		return sss;
	}


	public void setSss(String sss) {
		this.sss = sss;
	}
}
