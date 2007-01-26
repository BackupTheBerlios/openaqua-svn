/**
 * 
 */
package de.tmobile.cabu.db4o;

import java.util.ArrayList;
import com.db4o.ObjectContainer;
import com.db4o.ObjectSet;

/**
 * 
 *
 */
final public class ContractContainerFactory {
	final private static ContractContainerFactory Instance = new ContractContainerFactory();
	

	final public ContractContainer getContractContainer(final ObjectContainer database, final String name){
		ObjectSet result=database.get(new ContractContainer(name));
		if (result.hasNext()) {
			return (ContractContainer)result.next();
		} else {
			ContractContainer contractContainer = new ContractContainer(name);
			//contractContainer.contractMap  = new HashMap<ContractKey, Contract>(Configuration.getInstance().getMaxContracts());
			//contractContainer.contractMap  = database.ext().collections().newHashMap(Configuration.getInstance().getMaxContracts());
			//contractContainer.contractList  = database.ext().collections().newLinkedList();

			contractContainer.contractList  = new ArrayList<Contract>();
			//contractContainer.addContract(new Contract(12345678, " Hallo Ballo ", 100));
			//contractContainer.addContract(new Contract(87654321, " FOOOO BAAAR ", 100));
			database.set(contractContainer);
			database.commit();
			
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
