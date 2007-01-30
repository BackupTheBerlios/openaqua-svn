/**
 * 
 */
package de.tmobile.cabu.entities;

/**
 * 
 *
 */
public class Contract {

	private final ContractKey contractKey;
	private int value = 0;
	private final String stringId;
	private String stringValue;

	public Contract(int contractKey, int value) {
		super();
		this.contractKey = new ContractKey( contractKey );
		this.stringId = "stringId("+contractKey+")";
		this.value = value;
	}

	
	
	public Contract(int contractKey, String stringValue, int value) {
		super();
		this.contractKey = new ContractKey( contractKey );
		this.stringId = "stringId("+contractKey+")";
		this.stringValue = stringValue;
		this.value = value;
	}

	

	/* (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		final int PRIME = 31;
		int result = 1;
		result = PRIME * result + ((contractKey == null) ? 0 : contractKey.hashCode());
		return result;
	}


	/* (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 * 
	 * Two Contracts are equal if the keys are equal
	 */
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		final Contract other = (Contract) obj;
		if (contractKey == null) {
			if (other.contractKey != null)
				return false;
		} else if (!contractKey.equals(other.contractKey))
			return false;
		return true;
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
	public int getValue() {
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
		System.out.println("   Contract("+contractKey.getKey()+")\tvalue="+value);
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
