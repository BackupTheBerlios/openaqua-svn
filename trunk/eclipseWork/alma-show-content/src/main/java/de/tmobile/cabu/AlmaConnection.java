/**
 * 
 */
package de.tmobile.cabu;


import java.sql.SQLException;




/**
 * @author behrenan
 * 
 */
public class AlmaConnection {
	private Logger logger = Logger.getRootLogger();
	private TTConnection connection = null;
	private boolean allFine = false;

	
	AlmaConnection(final String driver) throws ClassNotFoundException {
		connection = new TTConnection(driver);
		allFine = true;
	}
	

	public void listTemplates(int whatToRun) {
		if (allFine != true) return;
		try {
			CSubTypeList.getInstances().refreshList(connection);
			CDescriptionList.getInstances().refreshList(connection);
			CCareDescriptionList.getInstances().refreshList(connection);
			//CIdentificationTemplatesList.getInstances().refresh(connection);
			//CAssocList.getInstances().refresh(connection);
			
			if (whatToRun == 0) {
				CSubTypeList.getInstances().print("SUBTYPE");
				CDescriptionList.getInstances().print("TA_DESCRIPTION");
				CCareDescriptionList.getInstances().print("TA_CARE_DESCRIPTION");
				//CIdentificationTemplatesList.getInstances().printTemplateIds("TEMPL_IDs");
				//CIdentificationTemplatesList.getInstances().printContractIds("CONTR_IDs");
				//CAssocList.getInstances().print("TA_ELEMENT_IDENT_ASSOC");
			}
			
			//if (whatToRun == 1) CIdentificationTemplatesList.getInstances().printTemplateIds("TEMPL_IDs");
			//if (whatToRun == 2) CIdentificationTemplatesList.getInstances().printContractIds("CONTR_IDs");
			//if (whatToRun == 3) CSubTypeList.getInstances().print("SUBTYPE");;
			//if (whatToRun == 4) CDescriptionList.getInstances().print("TA_DESCRIPITON");
			//if (whatToRun == 5) CCareDescriptionList.getInstances().print("TA_CARE_DESCRIPITON");
			//if (whatToRun == 6) CAssocList.getInstances().print("TA_ELEMENT_IDENT_ASSOC");
			
			
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
