/**
 * 
 */
package de.tmobile.cabu.db4o;

/**
 * @author tukaram
 *
 */
public class Contract {
	private static final long serialVersionUID = 1L;

	private int contractID;
	private int value = 0;
	
	public Contract (int contractID) {
		this.contractID = contractID;
	}

	public int getContractID() {
		return contractID;
	}

	public void setContractID(int contractID) {
		this.contractID = contractID;
	}

	public int getValue() {
		return value;
	}

	public void setValue(int value) {
		this.value = value;
	}

}
