/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class AlmaConnection {
	private final Logger logger = Logger.getRootLogger();

	AlmaConnection(final String driver, final String dsn) throws ClassNotFoundException {
		logger.info("Make Connection to: " + dsn);
		Configuration.getInstance().setConnection(new TTConnection(driver));
		Configuration.getInstance().getConnection().Connect(dsn);
	}

	public void Disconnect() {
		if (Configuration.getInstance().isError()) { return; }
		Configuration.getInstance().getConnection().Disconnect();
		logger.info("AlmaConnection: Disconnected");
	}

	public void listTemplates(final int whatToRun) {
		if (Configuration.getInstance().isError()) { return; }


		//Register (and load from TT) new DataList
		AlmaDataLoader.getInstances().addList(CElementIdentAssocList.getInstances());
		AlmaDataLoader.getInstances().addList(CIdentificationList.getInstances());
		AlmaDataLoader.getInstances().addList(CSubTypeList.getInstances());
		AlmaDataLoader.getInstances().addList(CDataTypeList.getInstances());
		AlmaDataLoader.getInstances().addList(CDescriptionList.getInstances());
		AlmaDataLoader.getInstances().addList(CCareDescriptionList.getInstances());
		AlmaDataLoader.getInstances().addList(CIdentification_CvList.getInstances());
		AlmaDataLoader.getInstances().addList(CIdentification_TyList.getInstances());
		AlmaDataLoader.getInstances().addList(CUnitTypeList.getInstances());
		AlmaDataLoader.getInstances().addList(CElementTypeList.getInstances());
		AlmaDataLoader.getInstances().addList(CElementSubtypeList.getInstances());
		AlmaDataLoader.getInstances().addList(CElementTmplList.getInstances());

		//Wait until they are finished
		AlmaDataLoader.getInstances().join();
		AlmaDataLoader.getInstances().clear();


		// Build higher Objects
		//BAccountList.getInstances().buildAccounts();
		// CIdentificationList.getInstances().print("IDENT");
		// BCustomerList.getInstances().buildCustomerList();

		// whatToRun = 1;
		if (whatToRun == 0) {
			//CSubTypeList.getInstances().print("TA_ELEMENT_SUBTYPE");
			//CDataTypeList.getInstances().print("ACM_TA_DATA_TYPE_CV");
			// CUnitTypeList.getInstances().print("ACM_TA_UNIT_TYPE_CV");
			CElementTypeList.getInstances().print("TA_ELEMENT_TYPE_CV");
			// CElementSubtypeList.getInstances().print("TA_ELEMENT_SUBTYPE_CV");
			// CIdentification_CvList.getInstances().print("TA_IDENTIFICATION_CV");
			// CCareDescriptionList.getInstances().print("TA_CARE_DESCRIPTION");
			//CDescriptionList.getInstances().print("TA_DESCRIPTION");
			//final UnifiedTableOutput otu = new UnifiedTableOutput();
			//CElementTmplList.getInstances().buildUnifiedPrintList("TA_ELEMENT_TMPL", otu);
			//otu.print();
			//CElementTmplList.getInstances().print("TA_ELEMENT_TMPL");
			//KnownElementAttributes.getInstances().dump();
			// 

			// CIdentification_TyList.getInstances().print("TA_IDENTIFICATION_TY");
			// CIdentificationList.getInstances().print("TA_IDENTIFICATION");
			// CIdentificationTemplatesList.getInstances().print("TA_IDENTIFICATION");
			// CElementIdentAssocList.getInstances().print("TA_ELEMENT_IDENT_ASSOC");
		}

		if (whatToRun == 1) {
			CSubTypeList.getInstances().print("SUBTYPE");
		}
		if (whatToRun == 2) {
			CCareDescriptionList.getInstances().print("TA_CARE_DESCRIPTION");
		}
		if (whatToRun == 3) {
			CDescriptionList.getInstances().print("TA_DESCRIPTION");
		}
		if (whatToRun == 4) {
			// CIdentificationContractsList.getInstances().print("TA_IDENTIFICATION");
		}
		if (whatToRun == 5) {
			CIdentificationList.getInstances().print("TA_IDENTIFICATION");
		}
		if (whatToRun == 6) {
			CElementIdentAssocList.getInstances().print("TA_ELEMENT_IDENT_ASSOC");
		}
	}
}
