package de.tmobile.cabu.sample;


import java.io.IOException;
import java.sql.Connection;
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


	private Contract getContractFromDb(final long id) {
		return (Contract) session.get(Contract.class, id);
	}



	public void setupDatabase() {
		Transaction trx = session.beginTransaction();
		for (int key = 1; key <= de.tmobile.cabu.loadtest.Configuration.getInstance().getMaxContracts(); key++) {
			try {
				Contract c = new Contract("value="+key, key);
				c.setName("name");
				c.setId(key);
				session.save(c);
			 } catch (Exception e) {
				logger.error("Error while persisting keys: "+e.getMessage());
			}

			if ((key % 1000) == 0) {
				logger.debug("created " + key + " keys");
			}
		}
		trx.commit();
		session.flush();
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
	private void executeRead(final long contractID) {
		Contract c = getContractFromDb(contractID); //get contract
		if (c == null) 	logger.error("RError: Didn't found Contract: " + contractID);
		if (c.getId() != contractID) 	logger.error("ID not equals should=" + contractID+ " is="+c.getId());
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
				contractID += 1;
				if (readTest == true) {
					executeRead(contractID);
					Stats.getInstance().addReadResults(1);
					//yield();
				} else {
					executeRead(contractID);
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
