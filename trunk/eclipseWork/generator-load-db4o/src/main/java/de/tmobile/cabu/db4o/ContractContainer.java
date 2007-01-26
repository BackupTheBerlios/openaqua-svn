/**
 * 
 */
package de.tmobile.cabu.db4o;

import java.util.Iterator;
import java.util.List;




/**
 * 
 *
 */
public class ContractContainer {
	List<Contract> contractList;
	String defaultString = "ABCDEFGEHA";
	String containerName;

	public ContractContainer (String name) {
		super();
		containerName = name;
	}

	public void addContract(Contract c) {
		//contractMap.put(c.getContractKey(), c);
		contractList.add(c);
	}

	public Contract getContract(int key) {
		return getContract(new ContractKey(key));
	}

	public void updateContract(Contract c) {
		addContract(c);
	}

	public Contract getContract(ContractKey key) {
		Iterator<Contract> i = contractList.iterator();
		while(i.hasNext()) {
			Contract c = i.next();
			if ( c.getContractKey().equals(key) ) {
				return c;
			}
		}
		return null;
	}

	public void removeContract(ContractKey key) {
		//contractMap.remove(key);
	}


	public void printContractList() {
		//Collection<Contract> collection = contractMap.values();
		//for ( Contract elem : collection ) 
		//	  System.out.println( elem.toString() );
	}

	/**
	 * @return the containerName
	 */
	public final String getContainerName() {
		return containerName;
	}

	/**
	 * @param containerName the containerName to set
	 */
	public final void setContainerName(String containerName) {
		this.containerName = containerName;
	}

	/**
	 * @return the contractList
	 */
	public List<Contract> getContractList() {
		return this.contractList;
	}

	/**
	 * @param contractList the contractList to set
	 */
	public void setContractList(List<Contract> contractList) {
		this.contractList = contractList;
	}

	/**
	 * @return the defaultString
	 */
	public String getDefaultString() {
		return this.defaultString;
	}

	/**
	 * @param defaultString the defaultString to set
	 */
	public void setDefaultString(String defaultString) {
		this.defaultString = defaultString;
	}

}
