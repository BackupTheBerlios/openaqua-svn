/**
 * 
 */
package de.tmobile.cabu;


import java.util.List;

import org.apache.log4j.Logger;

/**
 * @author behrenan
 * 
 */
public class AlmaConnection {
	private Logger logger = Logger.getRootLogger();
	private TTConnection connection = null;
	private boolean allFine = false;

	
	AlmaConnection() throws ClassNotFoundException {
		connection = new TTConnection();
		allFine = true;
	}

	public void listTemplates() {
		if (allFine != true) return;
		//connection.ListKnownSubTypes();
		List<Integer> ids = connection.getTemplateIds();
		logger.info("Found " + ids.size() + " Templates ");
		//connection.listTemplate(2);
		connection.listAllTemplates(ids);
	}
	
	public void Connect(final String dsn) {
		if (allFine != true) return;
		logger.info("Make Connection to: " + dsn);
		allFine = connection.Connect(dsn);
		
	}

	public void Disconnect() {
		if (allFine != true) return;
		logger.info("Disconnected");
		connection.Disconnect();		
	}

}
