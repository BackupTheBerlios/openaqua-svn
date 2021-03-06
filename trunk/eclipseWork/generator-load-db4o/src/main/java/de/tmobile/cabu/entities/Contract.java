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
	final private ContractKey contractKey;
	@Indexed
	private Integer value;
	private String stringValue;
	@Indexed
	private String name;

	public Contract(final int contractKey, final int value) {
		super();
		this.contractKey = new ContractKey( contractKey );
		this.value = new Integer(value);
	}

	
	
	public Contract(final int contractKey, final String stringValue, final int value) {
		super();
		this.contractKey = new ContractKey( contractKey );
		this.stringValue = stringValue;
		this.value = new Integer(value);
	}

	



	/**
	 * @return the contractKey
	 */
	public int getContractKeyAsInteger() {
		return contractKey.getKey();
	}

	/**
	 * @return the contractKey
	 */
	public ContractKey getContractKey() {
		return contractKey;
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


	public String getStringValue() {
		return stringValue;
	}



	/**
	 * @return the name
	 */
	public final String getName() {
		return name;
	}



	/**
	 * @param name the name to set
	 */
	public final void setName(String name) {
		this.name = name;
	}


}
