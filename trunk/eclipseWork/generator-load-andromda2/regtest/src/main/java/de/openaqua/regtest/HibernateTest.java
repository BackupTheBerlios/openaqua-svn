package de.openaqua.regtest;

import java.util.List;

import org.apache.log4j.Logger;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.cfg.Configuration;


import de.openaqua.dev.entities.City;
import de.openaqua.dev.entities.CityImpl;
import de.openaqua.dev.entities.Country;


public class HibernateTest extends RegTest{
	private static final SessionFactory sessionFactory = new Configuration().configure().buildSessionFactory();
	private final static Logger logger = Logger.getRootLogger();
	
	private Country  getGermany(Session session) {
		Query query = session.createQuery( "select c  from CountryImpl c where c.iso = :iso");
		query.setString("iso", "DE");
		List results = query.list();

		if (results.isEmpty()) {
			return null;
		} else {
			Country result =  (Country) results.get(0);
			logger.info("Found Germany. ID="+result.getId());
			return result;
		}
	}

	
	private void storeGermanCities() {
		Session session = sessionFactory.getCurrentSession();
		Transaction trx = session.beginTransaction();
		
		Country germany = getGermany(session); 
		City cologne = new CityImpl();
		cologne.getCountry().add(germany);
		cologne.setName("Köln");
		cologne.setZip("50931");
		
		session.save(cologne);
		logger.info("Saved Köln. ID="+cologne.getId());

		trx.commit();
		session.close();
		
	}
	
	public HibernateTest(final String name) {
		super(name);
	}
	
	public boolean RunTest() {
		storeGermanCities();
		storeGermanCities();
		storeGermanCities();
		storeGermanCities();
		return true;
	}
	

}
