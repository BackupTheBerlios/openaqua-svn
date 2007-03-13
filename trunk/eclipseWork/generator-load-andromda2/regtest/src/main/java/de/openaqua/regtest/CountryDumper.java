package de.openaqua.regtest;

import org.apache.log4j.Logger;

import de.openaqua.dev.entities.Country;

public class CountryDumper {
	private static Logger logger = Logger.getRootLogger();
	public void dumpCountry(final Country c) {
		String foo = "";
		foo += c.getIso();
		
		logger.info("Country: " + foo);
		
	}

}
