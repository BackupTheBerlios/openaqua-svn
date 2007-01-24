package de.tmobile.cabu.db4o;


import java.util.Iterator;
import java.util.List;
import java.util.Random;

import com.db4o.Db4o;
import com.db4o.ObjectContainer;
import com.db4o.ObjectSet;
import com.db4o.query.Query;

/**
 * @author behrenan
 *
 */
public class Db4oGenerator extends Thread{

	private int done = 0;
	private int maxContracts = Configuration.getInstance().getMaxContracts();
	private Random random = new Random();
	private ObjectContainer database;



	public Db4oGenerator(String threadName, ObjectContainer database)  {
		super( threadName); 
		this.database = database;
		//this.database = Db4o.openFile("foo.dat");
	}

	public void setupDatabase() {
		System.out.println("Create Contract ?");
		Db4o.configure().objectClass(Contract.class).objectField("contractID").indexed(true);
		for (int i = 0; i < Configuration.getInstance().getMaxContracts(); i++) {
			//System.out.println("Create Contract " + i);
			Contract c = new Contract();
			c.contractID = i;
			c.value = 0;
			database.set(c);
			if ((i % 100000) == 0) {
				System.out.println("created " + i + " Contracts");
				database.commit();
			}
		}
		
		database.commit();
		System.out.println("created " +Configuration.getInstance().getMaxContracts()+ " Contracts");
		
	}

	public void ListAllContracts() {
		List <Contract> list = database.query(Contract.class);
		for ( Iterator i = list.iterator(); i.hasNext(); )
		{
			Contract c = (Contract) i.next();
			System.out.println("Contains Contract " + c.contractID);
			
		}
	}


	private void executeRead() {
		//System.out.println("Execution in Thread: "+ getName());
		int contractID = Math.abs(random.nextInt()) % Configuration.getInstance().getMaxContracts();
		//System.out.println("Lookup for Contract " + contractID);

		Query query=database.query();
		query.constrain(Contract.class);
		query.descend("contractID").constrain(contractID);
		ObjectSet result=query.execute();
		if (!result.isEmpty()) {
			result.next();
			//Contract f = (Contract) result.next();
			//System.out.println("Found Contract: " + f.contractID + " look for " + contractID);
			
		}

		Stats.getInstance().addReadResults(1);
		yield();
	}

	protected void executeWrite() {
		//System.out.println("Execution in Thread: "+ getName());
		int contractID = Math.abs(random.nextInt()) % Configuration.getInstance().getMaxContracts();
		//System.out.println("Lookup for Contract " + contractID);

		Query query=database.query();
		query.constrain(Contract.class);
		query.descend("contractID").constrain(contractID);
		ObjectSet result=query.execute();
		if (!result.isEmpty()) {
			Contract f = (Contract) result.next();
			f.value = f.value+1;
			database.set(f);
			database.commit();
		}

		Stats.getInstance().addReadResults(1);
		yield();
	}


	/**
	 * The thread execution method
	 * runs endless
	 */
	public void run () {
		int loop = 0;
		try {
			for (int i = 0; i < Configuration.getInstance().getReqLoops(); i++){
				done = 0;
				while (done < maxContracts) {
					executeRead();
					//executeWrite();
					loop++;
					done++;
				}

			}
		} catch (Exception e) {
			System.out.println( "Murks");
			e.printStackTrace();
			return;
		}
	}
}
