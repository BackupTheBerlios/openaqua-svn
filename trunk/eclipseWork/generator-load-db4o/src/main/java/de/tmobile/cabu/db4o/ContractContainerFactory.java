/**
 * 
 */
package de.tmobile.cabu.db4o;

import com.db4o.ObjectContainer;
import com.db4o.ObjectSet;

/**
 * 
 *
 */
final public class ContractContainerFactory {
	final private static ContractContainerFactory INSTANCE = new ContractContainerFactory();
	
	final public static ContractContainerFactory getInstance() {
		return INSTANCE;
	}

	@SuppressWarnings("unchecked")
	final public ContractContainer getContractContainer(ObjectContainer database){
		ObjectSet result=database.get(new ContractContainer());
		if (result.hasNext()) {
			return (ContractContainer)result.next();
		} else {
			ContractContainer contractContainer = new ContractContainer();
			contractContainer.contractMap  = database.ext().collections().newHashMap(Configuration.getInstance().getMaxContracts());
			database.set(contractContainer);
			return contractContainer;
		}
	}
}
