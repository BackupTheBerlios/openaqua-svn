/**
 * 
 */
package de.tmobile.cabu.db4o;

import java.util.ArrayList;

import com.db4o.ObjectContainer;
import com.db4o.ObjectSet;

/**
 * @author tukaram
 *
 */
public class DbTestClass {
	public void simpleStore(ObjectContainer database) {
		database.set(new Contract(1234567, "erster Test", 87654321));
		database.set(new Contract(1234567, "erster Test", 87654321));
		database.set(new Contract(1234567, "erster Test", 87654321));
		database.set(new Contract(1234567, "erster Test", 87654321));
		database.set(new Contract(1234567, "erster Test", 87654321));
		ContractContainer cc = new ContractContainer("TestContainer");
		cc.contractList  = new ArrayList<Contract>();
		if (cc.addContract(new Contract(1234567, "erster Test", 87654321))!=true) {
			System.err.println("neuen Contract nicht zugefügt");
		}
		cc.dump();
		database.set(cc);
		database.commit();
	}


	public void simpleLoad(ObjectContainer database) {
		ObjectSet result=database.get(new Contract(1234567, null, 0));
		Contract c = (Contract)result.next();
		c.printContract();

		result=database.get(new ContractContainer("TestContainer"));
		ContractContainer cc = (ContractContainer)result.next();
		cc.dump();
	}

	public void simpleUpdate(ObjectContainer database) {
		ObjectSet result=database.get(new Contract(1234567, null, 0));
		Contract c = (Contract)result.next();
		c.setValue(10000);
		database.set(c);

		result=database.get(new ContractContainer("TestContainer"));
		ContractContainer cc = (ContractContainer)result.next();
		cc.setDefaultString("neuer defaultString");
		cc.addContract(new Contract(1111111, "haaaaaaaaaaaaa", 11));
		database.set(cc);
		
		database.commit();
	}
	
	
	public void dumpDatabase(ObjectContainer database) {
		ObjectSet result;

		System.out.println("----------Dump all Contracts---------------");
		result=database.get(Contract.class);
		while(result.hasNext()) {
			Contract c = (Contract)result.next();
			c.dump();
		}

		System.out.println("----------Dump all ContractContainer---------------");
		result=database.get(ContractContainer.class);
		while(result.hasNext()) {
			ContractContainer cc = (ContractContainer)result.next();
			cc.dump();
		}
		
		
		
		
	}
}
