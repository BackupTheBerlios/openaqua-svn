/**
 * 
 */
package de.tmobile.cabu;


import java.sql.SQLException;
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
		try {
			CSubTypeList.getInstances().refresh(connection);
			//CSubTypeList.getInstances().list(0);
			CTemplateList.getInstances().refresh(connection);
			CTemplateList.getInstances().list("TEMPLATE", 0);
			
		} catch (SQLException e) {
			connection.reportSQLException(e);
		}
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
