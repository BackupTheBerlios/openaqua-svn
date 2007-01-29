/**
 * 
 */
package de.tmobile.cabu.entities;

import java.util.ArrayList;
import com.db4o.ObjectContainer;
import com.db4o.ObjectSet;

import de.tmobile.cabu.db4o.DatabaseServerRegistry;

/**
 * 
 *
 */
final public class ContractContainerFactory {
	final private static ContractContainerFactory Instance = new ContractContainerFactory();


	final public ContractContainer getNewContractContainer(final String key, final String name){
		ObjectContainer database = DatabaseServerRegistry.getInstance().getClient(key);
		if (database == null) throw new NullPointerException("Got no database object by key \""+key+"\"");

		ObjectSet result=database.get(new ContractContainer(name));
		if (result.hasNext()) {
			return (ContractContainer)result.next();
		} else {
			ContractContainer contractContainer = new ContractContainer(name);
			//contractContainer.contractMap  = new HashMap<ContractKey, Contract>(Configuration.getInstance().getMaxContracts());
			//contractContainer.contractMap  = database.ext().collections().newHashMap(Configuration.getInstance().getMaxContracts());
			//contractContainer.contractList  = database.ext().collections().newLinkedList();

			contractContainer.contractList  = new ArrayList<Contract>();
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
