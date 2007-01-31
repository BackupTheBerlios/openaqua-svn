/**
 * 
 */
package de.tmobile.cabu.entities;

import com.db4o.config.annotations.Indexed;

/**
 * 
 *
 */
public class Contract {

	@Indexed
	public ContractKey contractKey = new ContractKey(0);
	@Indexed
	private Integer value = 0;
	private final String stringId;
	private String stringValue;

	public Contract(int contractKey, int value) {
		super();
		//this.contractKey = new ContractKey( contractKey );
		this.contractKey.key = contractKey;
		this.stringId = "stringId("+contractKey+")";
		this.value = new Integer(value);
	}

	
	
	public Contract(int contractKey, String stringValue, int value) {
		super();
		//this.contractKey = new ContractKey( contractKey );
		this.contractKey.key = contractKey;
		this.stringId = "stringId("+contractKey+")";
		this.stringValue = stringValue;
		this.value = new Integer(value);
	}

	



	/**
	 * @return the contractKey
	 */
	public int getContractKey() {
		//return contractKey.getKey();
		return contractKey.key;
	}


	/**
	 * @return the value
	 */
	public Integer getValue() {
		return value;
	}


	/**
	 * @param value the value to set
	 */
	public void setValue(int value) {
		this.value = value;
		this.stringValue = "value("+value+")";
	}

	public void dump() {
		//System.out.println("   Contract("+contractKey.getKey()+")\tvalue="+value);
		//contractKey.dump();
	}


	/**
	 * @return the stringId
	 */
	public String getStringId() {
		return stringId;
	}

	public String getStringValue() {
		return stringValue;
	}


}
