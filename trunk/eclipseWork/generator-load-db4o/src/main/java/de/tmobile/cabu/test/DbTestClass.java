/**
 * 
 */
package de.tmobile.cabu.db4o;

import java.util.ArrayList;
import java.util.List;

import com.db4o.ObjectContainer;
import com.db4o.ObjectSet;
import com.db4o.query.Predicate;
import de.tmobile.cabu.entities.*;

/**
 * @author tukaram
 *
 */
public class DbTestClass {
	public void simpleStore(ObjectContainer database) {
		ContractContainer cc = new ContractContainer("TestContainer");
		cc.contractList  = new ArrayList<Contract>();
		cc.addContract(new Contract(1234567, "erster Test", 87654321));
		database.set(cc);
		database.commit();
	}


	public void simpleLoad(ObjectContainer database) {
	}



	public void simpleUpdateContract(ObjectContainer database) {
		ObjectSet result=database.get(new Contract(1234567, null, 0));
		Contract c = (Contract)result.next();
		c.setValue(1);
		database.set(c);
		database.commit();

		c.setValue(2);
		database.set(c);
		database.commit();
	}

	public void simpleUpdateContractContainer(ObjectContainer database) {
		ObjectSet result=database.get(new ContractContainer("TestContainer"));
		ContractContainer cc = (ContractContainer)result.next();
		cc.setDefaultString("neuer defaultString");
		Contract a = new Contract(2222, "haaaaaaaaaaaaa", 11);
		cc.addContract(a);
		database.set(cc);
		database.commit();
	}

	public void dumpDatabase(ObjectContainer database) {
		System.out.println("----------Dump all ContractContainer---------------");
		List<ContractContainer> cc = database.query(new Predicate<ContractContainer>() {
			private static final long serialVersionUID = -8917750895495402842L;
			public boolean match(ContractContainer c) {
				return true;
			}
		});
		for (ContractContainer c : cc) 	c.dump();



		System.out.println("----------Dump all Contracts---------------");
		List<Contract> contracts = database.query(new Predicate<Contract>() {
			private static final long serialVersionUID = -8917750895495402841L;
			public boolean match(Contract c) {
				return true;
			}
		});
		for (Contract c : contracts) 	c.dump();


		System.out.println("----------Dump all ContractsKeys---------------");
		List<ContractKey> contractskeys = database.query(new Predicate<ContractKey>() {
			private static final long serialVersionUID = 1L;
			public boolean match(ContractKey c) {
				return true;
			}
		});
		for (ContractKey c : contractskeys) 		c.dump();




	}
}
