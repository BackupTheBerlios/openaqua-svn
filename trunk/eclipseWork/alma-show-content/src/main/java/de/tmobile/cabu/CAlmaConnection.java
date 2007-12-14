/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class CAlmaConnection {
	private final CLogger logger = CLogger.getRootLogger();

	CAlmaConnection(final String driver, final String dsn) throws ClassNotFoundException {
		logger.info("Make Connection to: " + dsn);
		CConfiguration.getInstance().setConnection(new TTConnection(driver));
		CConfiguration.getInstance().getConnection().Connect(dsn);
	}

	public void Disconnect() {
		if (CConfiguration.getInstance().isError()) { return; }
		CConfiguration.getInstance().getConnection().Disconnect();
		logger.info("AlmaConnection: Disconnected");
	}

	public void listTemplates(final int whatToRun) {
		if (CConfiguration.getInstance().isError()) { return; }


		//Register (and load from TT) new DataList
		CLogger.getRootLogger().debug("Start Loading");
		CAlmaDataLoader.getInstances().addList(ListCareDescription.getInstances());
		CAlmaDataLoader.getInstances().addList(ListDataType.getInstances());
		CAlmaDataLoader.getInstances().addList(ListDescription.getInstances());
		CAlmaDataLoader.getInstances().addList(ListElementIdentAssoc.getInstances());
		CAlmaDataLoader.getInstances().addList(ListElementSubtype.getInstances());
		CAlmaDataLoader.getInstances().addList(ListElementTmpl.getInstances());
		CAlmaDataLoader.getInstances().addList(ListElementType.getInstances());
		CAlmaDataLoader.getInstances().addList(ListIdentification_Cv.getInstances());
		CAlmaDataLoader.getInstances().addList(ListIdentification.getInstances());
		CAlmaDataLoader.getInstances().addList(ListIdentification_Ty.getInstances());
		CAlmaDataLoader.getInstances().addList(ListSubType.getInstances());
		CAlmaDataLoader.getInstances().addList(ListUnitType.getInstances());

		//Wait until they are finished
		CLogger.getRootLogger().debug("Loader Threads are running ...");
		CAlmaDataLoader.getInstances().join();
		CAlmaDataLoader.getInstances().clear();
		CLogger.getRootLogger().debug("Base Load is done");


		CLogger.getRootLogger().debug("Start Element Loading");
		CAlmaDataLoader.getInstances().addList(ListAccounts.getInstances());
		CAlmaDataLoader.getInstances().addList(ListCounters.getInstances());
		CAlmaDataLoader.getInstances().addList(ListCounterSets.getInstances());

		//Wait until finished
		CLogger.getRootLogger().debug("Loader Threads are running ...");
		CAlmaDataLoader.getInstances().join();
		CAlmaDataLoader.getInstances().clear();
		CLogger.getRootLogger().debug("Base Load is done");


		// whatToRun = 1;
		if (whatToRun == 0) {

			//ListIdentification_Ty.getInstances().print("TA_IDENTIFICATION_TY");
			//ListElementTmpl.getInstances().print("TA_ELEMENT_TMPL");
			//ListElementIdentAssoc.getInstances().print("TA_ELEMENT_IDENT_ASSOC");
			//ListIdentification.getInstances().print("TA_IDENTIFICATION");

			//ListElement.getInstances().print("TA_ELEMENT");
			//ListElementParentIds.getInstances().print("PARENT");

			//CSubTypeList.getInstances().print("TA_ELEMENT_SUBTYPE");
			//ListDataType.getInstances().print("TA_DATA_TYPE_CV");
			// CUnitTypeList.getInstances().print("ACM_TA_UNIT_TYPE_CV");
			//ListElementType.getInstances().print("TA_ELEMENT_TYPE_CV");
			ListAccounts.getInstances().print("Accounts");
			ListCounters.getInstances().print("Counters");
			ListCounterSets.getInstances().print("CounterSets");
			CKnownElementAttributes.getInstances().dump();

			// CElementSubtypeList.getInstances().print("TA_ELEMENT_SUBTYPE_CV");
			//CIdentification_CvList.getInstances().print("TA_IDENTIFICATION_CV");
			// CCareDescriptionList.getInstances().print("TA_CARE_DESCRIPTION");
			//CDescriptionList.getInstances().print("TA_DESCRIPTION");
			// CIdentification_TyList.getInstances().print("TA_IDENTIFICATION_TY");
			//CIdentificationList.getInstances().print("TA_IDENTIFICATION");
			// CIdentificationTemplatesList.getInstances().print("TA_IDENTIFICATION");
			//
		}

		if (whatToRun == 1) {
			//CSubTypeList.getInstances().print("SUBTYPE");
		}
		if (whatToRun == 2) {
			//CCareDescriptionList.getInstances().print("TA_CARE_DESCRIPTION");
		}
		if (whatToRun == 3) {
			//CDescriptionList.getInstances().print("TA_DESCRIPTION");
		}
		if (whatToRun == 4) {
			// CIdentificationContractsList.getInstances().print("TA_IDENTIFICATION");
		}
		if (whatToRun == 5) {
			//CIdentificationList.getInstances().print("TA_IDENTIFICATION");
		}
		if (whatToRun == 6) {
			//CElementIdentAssocList.getInstances().print("TA_ELEMENT_IDENT_ASSOC");
		}
	}
}
