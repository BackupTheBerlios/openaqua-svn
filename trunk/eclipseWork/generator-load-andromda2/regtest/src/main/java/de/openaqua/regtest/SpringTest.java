package de.openaqua.regtest;

import java.util.Iterator;
import java.util.List;

import de.openaqua.dev.entities.Country;
import de.openaqua.dev.entities.crud.CountryManageableDao;
import de.openaqua.dev.entities.crud.CountryManageableService;
import de.openaqua.dev.entities.crud.CountryValueObject;


public class SpringTest extends RegTest {

	public SpringTest(String name) {
		super(name);
	}

	
	public void listAllCountries() {
		
		CountryManageableDao dao = (CountryManageableDao) getBeanFactory().getFactory().getBean("CountryManageableDao");
		List list = dao.readAll();
		
		getLogger().warn("=====================List all Countries=====================");
		if (list.isEmpty()) {
			getLogger().error("List of all countries is empty");
		} else {
			Iterator iter = list.iterator();
			while(iter.hasNext()) {
				Country c  = (Country) iter.next();
				getLogger().warn("Found Country with ISO "+ c.getIso() + " and name " + c.getDescription());
			}
		}
	}
	
	
	
	
	public Country getCountry(final String iso, final String name) {
		
		CountryManageableDao dao = (CountryManageableDao) getBeanFactory().getFactory().getBean("CountryManageableDao");
		List list = dao.read(iso, null, null, null, null);
		if (!list.isEmpty()) {
			Country c =(Country) list.iterator().next(); 
			getLogger().warn("found country with ISO "+c.getIso() + " and id "+c.getId());
			return c;			
		} else {
			java.lang.Long[] em = {};
			Country c = dao.create(iso, name, "", null, em);
			getLogger().warn("created country with ISO "+c.getIso() + " and id "+c.getId());
			return c;
		}
		
		/*
		CountryService cs = (CountryService) bf.getFactory().getBean("countryService");
		CountryCriteria criteria =new CountryCriteria();
		criteria.setIso("DE");
		CountryVO[] results = cs.findCountriesByCriteria(criteria);
		if (results.length == 0) {
			CountryDao cdao = (CountryDao) bf.getFactory().getBean("countryDao");
			getLogger().warn("create Country " + iso + " and desc "+ name);
			return cdao.toCountryVO(cdao.create(iso, name, ""));
		} else {
			getLogger().warn("found Country " + results[0].getIso());
			return results[0];
		}
		*/
	}
	
	
	public CountryValueObject getCountryValueObject(final String iso) {
		CountryManageableService service = (CountryManageableService) getBeanFactory().getFactory().getBean("CountryManageableService");
		try {
			List list;
			list = service.read(iso, null, null, null, null);
			if (list.isEmpty()) return null;
			else return (CountryValueObject) list.get(0); 
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}
	}

	public boolean RunTest() {
		getLogger().info(" ===================== Run Spring Test =====================");
		
		//PhoneFormatDao phone = (PhoneFormatDao) bf.getFactory().getBean("phoneFormatDao");
		//phone.create("*");

		listAllCountries();
		
		Country de = getCountry("DE", "Germany");
		Country us = getCountry("US", "United States");
		Country uk = getCountry("UK", "United Kingdom");
		Country at = getCountry("AT", "Austria");

		listAllCountries();
		
		
		if (de == null) 	getLogger().error("Error with country de");
		if (us == null) 	getLogger().error("Error with country us");
		if (uk == null) 	getLogger().error("Error with country uk");
		if (at == null) 	getLogger().error("Error with country at");
		
		getLogger().info(" ===================== Run Services Test =====================");
	
		if (getCountryValueObject("AN") == null) getLogger().error("Got Null while loading AN");
		CountryValueObject c = getCountryValueObject("DE"); 
		if ( c == null){ getLogger().error("Got Null while loading DE"); } else { getLogger().error("Got "+c.getIso()+ " ID="+c.getId()); }
		
		return true;
	}



}
