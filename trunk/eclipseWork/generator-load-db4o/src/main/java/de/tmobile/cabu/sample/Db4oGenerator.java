package de.tmobile.cabu.sample;


import java.io.IOException;
import java.util.List;
import java.util.Random;
import org.apache.log4j.Logger;
import com.db4o.ObjectContainer;
import com.db4o.ObjectSet;
import com.db4o.query.Predicate;

import de.tmobile.cabu.db4o.DatabaseServerRegistry;
import de.tmobile.cabu.entities.Contract;
import de.tmobile.cabu.entities.ContractContainer;
import de.tmobile.cabu.entities.ContractContainerFactory;
import de.tmobile.cabu.loadtest.Stats;
import de.tmobile.cabu.loadtest.Configuration;


/**
 * @author behrenan
 *
 */
public class Db4oGenerator extends Thread{

	private int done = 0;
	final private int maxContracts = Configuration.getInstance().getMaxContracts();
	final private Random random = new Random();
	final private ObjectContainer database;
	final private boolean readTest;
	final private static Logger logger = Logger.getRootLogger();



	public Db4oGenerator(final String threadName, final String key, boolean readTest) throws IOException  {
		super(threadName);
		//init the class
		this.database = DatabaseServerRegistry.getInstance().getClient(key, "test", "test");
		this.readTest = readTest;

	}

	public void setupDatabase() {		
		//create a default contract container
		ContractContainer container = ContractContainerFactory.getInstance().getNewContractContainer(database, "Sample ContractContainer");
		container.setDefaultString("Sample Container");

		for (int key = 1; key <= Configuration.getInstance().getMaxContracts(); key++) {
			logger.debug("Create Contract " + key);
			container.addContract(new Contract(key, 1));

			if ((key % 100000) == 0) {
				logger.debug("created " + key + " Contracts");
				database.set(container);
				database.commit();
			}

		}
		database.set(container);
		database.commit();
		logger.info("created " +Configuration.getInstance().getMaxContracts()+ " Contracts");
	}

	
	
	public void ListAllContracts() {
		/*
		List<ContractContainer> cc = database.query(new Predicate<ContractContainer>() {
			private static final long serialVersionUID = -4653770118856489547L;
			public boolean match(ContractContainer c) {		return true; }
		});
		for (ContractContainer c : cc) 	c.dump();
		*/
	}


	private void executeRead() {
		//random contractID
		int contractID = 1+Math.abs(random.nextInt()) % Configuration.getInstance().getMaxContracts();
		logger.info("Look for Contract with ID "+contractID);


		//get contract
		//Contract f = contractContainer.getContract(contractID);
		Contract f = null;
		ObjectSet result = database.get(new Contract(contractID, 0));
		if (result.hasNext()) {
			f = (Contract)result.next();
		} else {
			logger.error("nothing found" + contractID);
		}
			

		//check result
		if (f != null) {
			if (f.getContractKey().getKey() != contractID) {
				logger.error("Error: Found Contract: " + f.getContractKey().getKey() + " looked for " + contractID);
			}
		} else {
			logger.error("RError: Didn't found Contract: " + contractID);
		}

		Stats.getInstance().addReadResults(1);
		//yield();
	}

	private void executeWrite() {
		//random contractID
		/*		
		int contractID = 1+Math.abs(random.nextInt()) % Configuration.getInstance().getMaxContracts();

		//get contract
		Contract c = contractContainer.getContract(new ContractKey(contractID));

		//check result
		if (c != null) {
			if (c.getContractKey().getKey() != contractID) {
				System.err.println("Error: Found Contract: " + c.getContractKey().getKey() + " looked for " + contractID);
			} else {
				//System.out.println("Found Contract: " + f.getContractKey().getKey() + " with value: " + f.getValue());
				c.setValue(c.getValue()+1);
				//contractContainer.removeContract(new ContractKey(contractID));
				//contractContainer.addContract(c);
				database.commit();
			}
		} else {
			System.err.println("WError: Didn't found Contract: " + contractID);
		}

		Stats.getInstance().addWriteResults(1);
		//yield();
		 */
	}


	/**
	 * The thread execution method
	 */
	public void run () {
		int loop = 0;
		for (int i = 0; i < Configuration.getInstance().getReqLoops(); i++){
			done = 0;
			while (done < maxContracts) {
				if (readTest == true) {
					executeRead();
				} else {
					//executeRead();
					//executeWrite();
				}
				loop++;
				done++;
			}
		}
		//dump the found contract containers
		/*
		List<ContractContainer> cc = database.query(new Predicate<ContractContainer>() {
			private static final long serialVersionUID = -4653770118856489546L;
			public boolean match(ContractContainer c) {		return true; }
		});
		for (ContractContainer c : cc) 	c.dump();
		*/
		if (database != null)		database.close();
	}
}
