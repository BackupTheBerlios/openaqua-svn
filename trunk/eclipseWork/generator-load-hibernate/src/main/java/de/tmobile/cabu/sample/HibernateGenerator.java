package de.tmobile.cabu.sample;


import java.io.IOException;
import java.util.Random;
import org.apache.log4j.Logger;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.cfg.AnnotationConfiguration;
import org.hibernate.cfg.Configuration;
import org.hibernate.classic.Session;

import de.tmobile.cabu.entities.Contract;
import de.tmobile.cabu.entities.ContractKey;
import de.tmobile.cabu.loadtest.Stats;



/**
 * @author behrenan
 *
 */
public class HibernateGenerator extends Thread{

	private int done = 0;
	final private int maxContracts = de.tmobile.cabu.loadtest.Configuration.getInstance().getMaxContracts();
	final private Random random = new Random();
	final private boolean readTest;
	final private static Logger logger = Logger.getRootLogger();
	//private AnnotationConfiguration configuration;
	//private Configuration configuration;
	private SessionFactory sessionFactory;
	private Session session;
	 



	public HibernateGenerator(final String threadName, final String key, boolean readTest) throws IOException  {
		super(threadName);
		//configuration = new Configuration();
		//sessionFactory = configuration.buildSessionFactory();
		sessionFactory = new org.hibernate.cfg.Configuration().configure("hibernate.cfg.mapping.xml").buildSessionFactory();
		session = sessionFactory.openSession();
		//init the class
		//this.database = DatabaseServerRegistry.getInstance().getClient(key, "test", "test");
		this.readTest = readTest;

	}

	
	private Contract getContractFromDbByName(final int id) {
		/*
		Query query=database.query();
		query.constrain(Contract.class);
		query.descend("name").constrain("name"+id);
		ObjectSet result=query.execute();

		if (result.hasNext()) {
			return (Contract)result.next();
		} else {
			logger.error("No matching contract found");
			return null;
		}
		*/
		 
		return null;
	}
	

	private Contract getContractFromDb(final int id) {
		return null;
		/*
		Query query=database.query();
		query.constrain(Contract.class);
		query.descend("contractKey").constrain(new ContractKey(id));
		ObjectSet result=query.execute();

		if (result.hasNext()) {
			return (Contract)result.next();
		} else {
			logger.error("No matching contract found");
			return null;
		}
		*/
	}

	private ContractKey getContractKeyFromDb(final int id) {
		return null;
		/*
		Query query=database.query();
		query.constrain(ContractKey.class);
		query.descend("key").constrain(id);
		ObjectSet result=query.execute();

		if (result.hasNext()) {
			return (ContractKey)result.next();
		} else {
			logger.error("No matching contract found");
			return null;
		}
		*/
	}
	
	
	public void setupDatabase() {
		Transaction trx = session.beginTransaction();
		for (int key = 0; key <= de.tmobile.cabu.loadtest.Configuration.getInstance().getMaxContracts(); key++) {
			session.save(new ContractKey(key));
			if ((key % 1000) == 0) {
				logger.debug("created " + key + " keys");
			}
		}
		trx.commit();
		logger.debug("created " + de.tmobile.cabu.loadtest.Configuration.getInstance().getMaxContracts() + " Contracts");
		logger.info("setup Database created " +de.tmobile.cabu.loadtest.Configuration.getInstance().getMaxContracts()+ " Contracts");
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
		for (int i = 0; i < de.tmobile.cabu.loadtest.Configuration.getInstance().getReqLoops(); i++){
			done = 0;
			while (done < maxContracts) {
				int contractID = Math.abs(random.nextInt()) % de.tmobile.cabu.loadtest.Configuration.getInstance().getMaxContracts(); //random contractID
				if (readTest == true) {
					executeReadKeys(contractID);
					//executeRead(contractID);
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
