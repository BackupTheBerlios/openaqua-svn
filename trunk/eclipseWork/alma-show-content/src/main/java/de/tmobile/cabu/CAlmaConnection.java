/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class CAlmaConnection {
	private final static CAlmaConnection INSTANCE = new CAlmaConnection();

	public final static CAlmaConnection getInstances() {
		return INSTANCE;
	}

	private CAlmaConnection() {
		super();
	}


	public void listTemplates(final int whatToRun) {

		//Register (and load from TT) new DataList
		CLogger.getRootLogger().debug("Start Loading");
		CAlmaDataLoader.getInstances().addList(ListCareDescription.getInstances());
		CAlmaDataLoader.getInstances().addList(ListDataType.getInstances());
		CAlmaDataLoader.getInstances().addList(ListDescription.getInstances());
		CAlmaDataLoader.getInstances().addList(ListElementIdentAssoc.getInstances());
		CAlmaDataLoader.getInstances().addList(ListElementSubtype.getInstances());
		CAlmaDataLoader.getInstances().addList(ListElementType.getInstances());
		CAlmaDataLoader.getInstances().addList(ListIdentification_Cv.getInstances());
		CAlmaDataLoader.getInstances().addList(ListIdentification.getInstances());
		CAlmaDataLoader.getInstances().addList(ListIdentification_Ty.getInstances());
		CAlmaDataLoader.getInstances().addList(ListSubType.getInstances());
		CAlmaDataLoader.getInstances().addList(ListUnitType.getInstances());

		//Wait until they are finished
		CLogger.getRootLogger().debug("Loader Threads are running ...");
		CAlmaDataLoader.getInstances().waitForFinish();
		CLogger.getRootLogger().debug("Base Load is done");


		CLogger.getRootLogger().debug("Start Element Loading");
		CAlmaDataLoader.getInstances().addList(ListAccountsTemplates.getInstances());
		CAlmaDataLoader.getInstances().addList(ListCounterSetTemplates.getInstances());
		CAlmaDataLoader.getInstances().addList(ListCountersTemplates.getInstances());
		CAlmaDataLoader.getInstances().addList(ListAccounts.getInstances());
		CAlmaDataLoader.getInstances().addList(ListCounters.getInstances());
		CAlmaDataLoader.getInstances().addList(ListCounterSets.getInstances());

		//Wait until finished
		CLogger.getRootLogger().debug("Loader Threads are running ...");
		CAlmaDataLoader.getInstances().waitForFinish();
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
			ListAccountsTemplates.getInstances().print("TMPL");
			/*
			ListCountersTemplates.getInstances().print("TMPL");
			ListCounterSetTemplates.getInstances().print("TMPL");
			ListAccounts.getInstances().print("Accounts");
			ListCounters.getInstances().print("Counters");
			ListCounterSets.getInstances().print("CounterSets");
			*/
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
