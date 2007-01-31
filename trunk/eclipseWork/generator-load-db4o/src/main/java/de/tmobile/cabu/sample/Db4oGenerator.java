package de.tmobile.cabu.sample;


import java.io.IOException;
import java.util.List;
import java.util.Random;
import org.apache.log4j.Logger;
import com.db4o.ObjectContainer;
import com.db4o.query.Predicate;

import de.tmobile.cabu.db4o.DatabaseServerRegistry;
import de.tmobile.cabu.entities.Contract;
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



	public Db4oGenerator(final String threadName, final String key, boolean readTest) throws IOException  {
		super(threadName);
		//init the class
		this.database = DatabaseServerRegistry.getInstance().getClient(key, "test", "test");
		this.readTest = readTest;

	}


	private Contract getContractFromDb(final int id) {
		//final ContractKey key = new ContractKey(id);
		final int key = id;
		List<Contract> ccl = database.query(new Predicate <Contract> () {
			private static final long serialVersionUID = -8834454829647279541L;
			public boolean match(final Contract concon){
				//return concon.getContractKey() == key;
				//return concon.getValue() == key;
				return concon.contractKey.key == key;
			}
		});

		if ((ccl==null) || (ccl.isEmpty() == true)) {
			logger.error("No matching contract found");
			return null;
		} else {
			return ccl.listIterator().next();
		}
	}

	private ContractKey getContractKeyFromDb(final int id) {
		//get contract Container
		List<ContractKey> ccl = database.query(new Predicate <ContractKey> () {
			private static final long serialVersionUID = -8930087358020376676L;
			public boolean match(final ContractKey concon){
				return concon.getKey() == id;
			}
		});

		if ((ccl==null) || (ccl.isEmpty() == true)) {
			logger.error("No matching contractkey found");
			return null;
		} else {
			return ccl.listIterator().next();
		}
	}
	
	
	public void setupDatabase() {		
		for (int key = 0; key <= Configuration.getInstance().getMaxContracts(); key++) {
			Contract c = new Contract(key, key);
			database.set(c);
			if ((key % 1000) == 0) {
				logger.debug("created " + key + " Contracts");
			}

		}
		logger.debug("created " + Configuration.getInstance().getMaxContracts() + " Contracts");
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


	private void executeRead(final int contractID) {
		Contract c = getContractFromDb(contractID); //get contract
		if (c == null) 	logger.error("RError: Didn't found Contract: " + contractID);
	}

	private void executeReadKeys(final int contractID) {
		ContractKey c = getContractKeyFromDb(contractID); //get contract
		if (c == null) 	logger.error("RError: Didn't found Contract: " + contractID);
	}
	

	/**
	 * The thread execution method
	 */
	public void run () {
		int loop = 0;
		for (int i = 0; i < Configuration.getInstance().getReqLoops(); i++){
			done = 0;
			while (done < maxContracts) {
				int contractID = Math.abs(random.nextInt()) % Configuration.getInstance().getMaxContracts(); //random contractID
				if (readTest == true) {
					//executeRead(contractID);
					Stats.getInstance().addReadResults(1);
					//yield();
				} else {
					//executeRead(contractID);
					executeReadKeys(contractID);
					Stats.getInstance().addWriteResults(1);
					//yield();
				}
				loop++;
				done++;
			}
		}
		if (database != null)		database.close();
	}
}
