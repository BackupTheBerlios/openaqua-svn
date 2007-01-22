package de.tmobile.cabu.db4o;


import java.util.Enumeration;
import java.util.Iterator;
import java.util.List;
import java.util.Random;

import com.db4o.Db4o;
import com.db4o.ObjectContainer;
import com.db4o.ObjectSet;
import com.db4o.query.Predicate;
import com.db4o.query.Query;

/**
 * @author behrenan
 *
 */
public class TTGenerator extends Thread{

	private int done = 0;
	private int maxContracts = Configuration.getInstance().getMaxContracts();
	private Random random = new Random();
	private ObjectContainer database;



	/**
	 * Constructor
	 * @throws ClassNotFoundException 
	 */
	public TTGenerator(String threadName)  {
		super( threadName); 

	}

	public void setupDatabase() {
		for (int i = 0; i < Configuration.getInstance().getMaxContracts(); i++) {
			System.out.println("Create Contract " + i);

			Contract c = new Contract(i);
			c.setValue(100);
			database.set(c);
		}
		database.commit();
	}

	public void ListAllContracts() {
		List <Contract> list = database.query(Contract.class);
		for ( Iterator i = list.iterator(); i.hasNext(); )
		{
			Contract c = (Contract) i.next();
			System.out.println("Contains Contract " + c.getContractID());
			
		}
	}

	/**
	 * Init this thread
	 *
	 */
	public void Init(){
		database =Db4o.openFile("foo.dat");
	}

	public void Close(){
		database.close();
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
			//System.out.println("Found for Contract " + contractID);
			Contract f = (Contract) result.next();
			f.setValue(f.getValue()+1);
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
