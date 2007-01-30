/**
 * 
 */
package de.tmobile.cabu.entities;

import java.util.HashMap;
import de.tmobile.cabu.loadtest.Configuration;

import com.db4o.ObjectContainer;
import com.db4o.ObjectSet;


/**
 * 
 *
 */
final public class ContractContainerFactory {
	final private static ContractContainerFactory Instance = new ContractContainerFactory();


	final public ContractContainer getNewContractContainer(final ObjectContainer database, final String name){
		ObjectSet result=database.get(new ContractContainer(name));
		if (result.hasNext()) {
			return (ContractContainer)result.next();
		} else {
			ContractContainer contractContainer = new ContractContainer(name);
			contractContainer.contractList  = new HashMap<ContractKey, Contract>(Configuration.getInstance().getMaxContracts());
			//contractContainer.contractMap  = database.ext().collections().newHashMap(Configuration.getInstance().getMaxContracts());
			//contractContainer.contractList  = database.ext().collections().newLinkedList();

			//contractContainer.contractList  = new ArrayList<Contract>();
			contractContainer.setDefaultString("defaultString");
			return contractContainer;
		}
	}


	/**
	 * @return the instance
	 */
	public static final ContractContainerFactory getInstance() {
		return Instance;
	}
}
