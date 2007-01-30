/**
 * 
 */
package de.tmobile.cabu.entities;

import java.util.Iterator;
import java.util.List;
import java.util.Map;




/**
 * 
 *
 */
public class ContractContainer {
	//public List<Contract> contractList;
	public Map<ContractKey, Contract> contractList;
	
	private String defaultString;
	final private String containerName;

	public ContractContainer (final String name) {
		super();
		containerName = name;
	}
	
	public void dump() {
		System.out.println("ContractContainer=("+containerName+") defaultStrin="+defaultString);
		if (contractList == null) 	return;
		for(Iterator i = contractList.values().iterator(); i.hasNext(); ) 	((Contract)i.next()).dump();
	}

	
	public boolean addContract(Contract c) {
		contractList.put(c.getContractKey(), c);
		return true;
	}

	
	public Contract getContract(int key) {
		return getContract(new ContractKey(key));
	}

	
	public void updateContract(Contract c) {
		addContract(c);
	}


	public Contract getContract(ContractKey key) {
		Iterator<Contract> i = contractList.values().iterator();
		while(i.hasNext()) {
			Contract c = i.next();
			if ( c.getContractKey().equals(key) ) {
				return c;
			}
		}
		return null;
	}

	/**
	 * @return the containerName
	 */
	public String getContainerName() {
		return this.containerName;
	}

	/**
	 * @return the contractList
	 */
	public List<Contract> getContractList() {
		//return this.contractList.values();
		return null;
	}

	/**
	 * @param contractList the contractList to set
	 */
	public void setContractList(List<Contract> contractList) {
		//this.contractList = contractList;
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
