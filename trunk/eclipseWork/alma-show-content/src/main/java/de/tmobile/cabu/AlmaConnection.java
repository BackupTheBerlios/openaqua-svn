/**
 * 
 */
package de.tmobile.cabu;

import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;

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

		try {
			// A list for all List (-threads)
			final List<Thread> threadList = new LinkedList<Thread>();
			threadList.add(new Thread(CSubTypeList.getInstances()));
			threadList.add(new Thread(CDescriptionList.getInstances()));
			threadList.add(new Thread(CCareDescriptionList.getInstances()));
			threadList.add(new Thread(CIdentificationList.getInstances()));
			threadList.add(new Thread(CElementIdentAssocList.getInstances()));
			threadList.add(new Thread(CIdentification_CvList.getInstances()));
			threadList.add(new Thread(CIdentification_TyList.getInstances()));

			// start the loader part of all lists once
			ListIterator<Thread> iter = threadList.listIterator();
			while (iter.hasNext()) {
				iter.next().start();
			}

			// and wait for finishing their jobs
			iter = threadList.listIterator();
			while (iter.hasNext()) {
				iter.next().join();
			}

		} catch (final InterruptedException e) {
			Logger.getRootLogger().error("Something went wrong while loading data...");
			e.printStackTrace();
			Configuration.getInstance().getConnection().Disconnect();
			return;
		}

		// whatToRun = 1;
		if (whatToRun == 0) {
			// CSubTypeList.getInstances().print("SUBTYPE");
			// CDescriptionList.getInstances().print("TA_DESCRIPTION");
			// CCareDescriptionList.getInstances().print("TA_CARE_DESCRIPTION");
			CIdentification_CvList.getInstances().print("TA_IDENTIFICATION_CV");
			CIdentification_TyList.getInstances().print("TA_IDENTIFICATION_TY");
			CIdentificationList.getInstances().print("TA_IDENTIFICATION");
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
			CIdentificationContractsList.getInstances().print("TA_IDENTIFICATION");
		}
		if (whatToRun == 5) {
			CIdentificationList.getInstances().print("TA_IDENTIFICATION");
		}
		if (whatToRun == 6) {
			CElementIdentAssocList.getInstances().print("TA_ELEMENT_IDENT_ASSOC");
		}
	}
}
