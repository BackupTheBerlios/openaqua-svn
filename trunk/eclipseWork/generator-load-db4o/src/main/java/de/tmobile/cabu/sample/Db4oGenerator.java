package de.tmobile.cabu.sample;


import java.io.IOException;
import java.util.Iterator;
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
import de.tmobile.cabu.entities.ContractKey;
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
	final private String containerName = "TestContainer";



	public Db4oGenerator(final String threadName, final String key, boolean readTest) throws IOException  {
		super(threadName);
		//init the class
		this.database = DatabaseServerRegistry.getInstance().getClient(key, "test", "test");
		this.readTest = readTest;

	}

	private ContractContainer getContainerFromDb(final String name) {
		//get contract Container
		List<ContractContainer> ccl = database.query(new Predicate <ContractContainer> () {
			private static final long serialVersionUID = 5792132993232582586L;
			public boolean match(final ContractContainer concon){
				return concon.getContainerName().equals(name);
			}
		});

		if (ccl==null) {
			logger.error("No matching contract container found");
			return null;
		} else {
			Iterator<ContractContainer> i = ccl.listIterator();
			return i.next();
		}
	}

	private Contract getContractFromDb(final int id) {
		//get contract Container
		final ContractKey key = new ContractKey(id);  
		List<Contract> ccl = database.query(new Predicate <Contract> () {
			private static final long serialVersionUID = 5792132993232582586L;
			public boolean match(final Contract concon){
				return concon.getContractKey().equals(key);
			}
		});

		if (ccl==null) {
			logger.error("No matching contract found");
			return null;
		} else {
			Iterator<Contract> i = ccl.listIterator();
			return i.next();
		}
	}

	private ContractKey getContractKeyFromDb(final int id) {
		//get contract Container
		List<ContractKey> ccl = database.query(new Predicate <ContractKey> () {
			private static final long serialVersionUID = 5792232993232582386L;
			public boolean match(final ContractKey concon){
				return concon.getKey() == id;
			}
		});

		if (ccl==null) {
			logger.error("No matching contractkey found");
			return null;
		} else {
			;
			return ccl.listIterator().next();
		}
	}
	
	
	public void setupDatabase() {		
		//create a default contract container
		//ContractContainer container = ContractContainerFactory.getInstance().getNewContractContainer(database, containerName);
		//container.setDefaultString("container before first store");
		//database.set(container);
		//database.commit();
		//container = getContainerFromDb(containerName);
		//container.setDefaultString("container after first store");
		

		for (int key = 1; key <= Configuration.getInstance().getMaxContracts(); key++) {
			//logger.debug("Create Contract " + key);
			Contract c = new Contract(key, 1);
			//container.addContract(c);
			database.set(c);
			if ((key % 1000) == 0) {
				logger.debug("created " + key + " Contracts");
			}

		}
		//database.set(container);
		database.commit();
		logger.info("setup Database created " +Configuration.getInstance().getMaxContracts()+ " Contracts");
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

		//get contract
		ContractContainer cc = getContainerFromDb(containerName);
		Contract c = cc.getContract(contractID);

		//check result
		if (c != null) {
			if (c.getContractKey().getKey() != contractID) {
				logger.error("Error: Found Contract: " + c.getContractKey().getKey() + " looked for " + contractID);
			}
		} else {
			logger.error("RError: Didn't found Contract: " + contractID);
		}


		Stats.getInstance().addReadResults(1);
		yield();

	}

	private void executeReadKeys() {
		//random contractID
		int contractID = 1+Math.abs(random.nextInt()) % Configuration.getInstance().getMaxContracts();

		//get contract
		ContractKey c = getContractKeyFromDb(contractID);

		//check result
		if (c == null) {
			logger.error("RError: Didn't found ContractKey: " + contractID);
		}


		Stats.getInstance().addReadResults(1);
		yield();

	}
	
	private void executeWrite() {
		//random contractID
		int contractID = 1+Math.abs(random.nextInt()) % Configuration.getInstance().getMaxContracts();

		//get contract
		Contract c = getContractFromDb(contractID);

		//check result
		if (c != null) {
			if (c.getContractKey().getKey() != contractID) {
				logger.error("Error: Found Contract: " + c.getContractKey().getKey() + " looked for " + contractID);
			}
		} else {
			logger.error("RError: Didn't found Contract: " + contractID);
		}


		Stats.getInstance().addWriteResults(1);
		yield();
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
					executeReadKeys();
				} else {
					executeWrite();
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
