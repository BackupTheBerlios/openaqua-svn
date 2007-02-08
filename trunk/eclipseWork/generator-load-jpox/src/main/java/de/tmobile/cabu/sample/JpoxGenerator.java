/**
 * 
 */
package de.tmobile.cabu.sample;

import java.io.IOException;
import java.util.Random;

import org.apache.log4j.Logger;

import de.tmobile.cabu.entities.Contract;
import de.tmobile.cabu.entities.ContractKey;
import de.tmobile.cabu.loadtest.Configuration;
import de.tmobile.cabu.loadtest.Stats;

/**
 * @author behrenan
 *
 */
public class JpoxGenerator extends Thread{

	private int done = 0;
	final private int maxContracts = Configuration.getInstance().getMaxContracts();
	final private Random random = new Random();
	final private boolean readTest;
	final private static Logger logger = Logger.getRootLogger();



	public JpoxGenerator(final String threadName, final String key, boolean readTest) throws IOException  {
		super(threadName);
		this.readTest = readTest;
	}

	
	private Contract getContractFromDbByName(final int id) {
		return null;
	}
	

	private Contract getContractFromDb(final int id) {
			return null;
	}

	private ContractKey getContractKeyFromDb(final int id) {
			return null;
	}
	
	
	public void setupDatabase() {		
		for (int key = 0; key <= Configuration.getInstance().getMaxContracts(); key++) {
			Contract c = new Contract(key, key);
			c.setName("name"+key);
			//database.set(c);
			if ((key % 1000) == 0) {
				logger.debug("created " + key + " Contracts");
			}

		}
		logger.debug("created " + Configuration.getInstance().getMaxContracts() + " Contracts");
		//database.commit();
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

	
	private void executeReadByName(final int contractID) {
		Contract c = getContractFromDbByName(contractID); //get contract
		if (c.getContractKeyAsInteger() != contractID) {
			logger.error("RError: Returned Contract has a wrong ID: " + c.getContractKeyAsInteger() + " expected was "+contractID);
		}
		if (c == null) 	logger.error("RError: Didn't found Contract: " + contractID);
	}

	private void executeRead(final int contractID) {
		Contract c = getContractFromDb(contractID); //get contract
		if (c.getContractKeyAsInteger() != contractID) {
			logger.error("RError: Returned Contract has a wrong ID: " + c.getContractKeyAsInteger() + " expected was "+contractID);
		}
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
					executeRead(contractID);
					executeReadByName(contractID);
					//executeReadByName(contractID);					
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
		//if (database != null)		database.close();
	}
	

}
