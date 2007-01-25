/**
 * 
 */
package de.tmobile.cabu.db4o;

import java.util.Collection;
import java.util.Map;



/**
 * 
 *
 */
public class ContractContainer {
	Map<ContractKey, Contract> contractMap;
	public ContractContainer () {
		super();
	}

	
	public void addContract(Contract c) {
		contractMap.put(c.getContractKey(), c);
	}
	
	
	public Contract getContract(ContractKey key) {
		return (Contract) contractMap.get(key);
	}

	public void updateContract(Contract c) {
		contractMap.put(c.getContractKey(), c);
	}
	
	public void removeContract(ContractKey key) {
		contractMap.remove(key);
	}
	
	
	public void printContractList() {
		//Collection<Contract> collection = contractMap.
		//for ( Contract elem : collection ) 
		//	  System.out.println( elem.toString() );
	}
	
}
