package de.tmobile.cabu.sample;


import java.io.IOException;
import java.util.Random;
import org.apache.log4j.Logger;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.classic.Session;

import de.tmobile.cabu.entities.Contract;
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
		sessionFactory = new org.hibernate.cfg.Configuration().configure("hibernate.cfg.mapping.xml").buildSessionFactory();
		session = sessionFactory.openSession();
		this.readTest = readTest;
	}




	private Contract getContractFromDb(final String msisdn) {
		org.hibernate.Query queryObject = session.createQuery("from de.tmobile.cabu.entities.ContractImpl as Contract where Contract.msisdn = ?");
        queryObject.setParameter(0, msisdn);
        java.util.List results = queryObject.list();
        if (results.size()>0) {
        	return (Contract)results.get(0);        	
        } else {
        	return null;
        }
	}



	public void setupDatabase() {
		Transaction trx = session.beginTransaction();
		for (int key = 1; key <= de.tmobile.cabu.loadtest.Configuration.getInstance().getMaxContracts(); key++) {
			try {
				Contract c = Contract.Factory.newInstance();
				c.setMsisdn("49160"+key);
				c.setContractId("ctrct"+key);
				c.setValidFrom(1000000);
				c.setValidTo(0);
				session.save(c);
			 } catch (Exception e) {
				logger.error("Error while persisting keys: "+e.getMessage());
			}

			if ((key % 1000) == 0) {
				logger.debug("created " + key + " keys");
				trx.commit();
				session.flush();
				trx = session.beginTransaction();
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
	private void executeRead(final int contractID) {
		final String msisdn = "49160"+contractID;
		Contract c = getContractFromDb(msisdn); //get contract
		if (c == null) 	logger.error("RError: Didn't found Contract: " + contractID);
		if (!c.getMsisdn().equals(msisdn) ) 	logger.error("MSISDN not equals should=" + msisdn+ " is="+c.getMsisdn());
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
