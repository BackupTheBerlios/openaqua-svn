/**
 * 
 */
package de.tmobile.cabu;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Iterator;

/**
 * @author behrenan
 * 
 */
public class BCustomerList extends CBaseList {
	private static BCustomerList INSTANCE = new BCustomerList();

	public static BCustomerList getInstances() {
		return INSTANCE;
	}

	public void buildCustomerList() {
		final int msisdnCv = CIdentification_CvList.getInstances().getMsisdnTypeId();
		final int contraCv = CIdentification_CvList.getInstances().getContractidTypeId();
		Logger.getRootLogger().debug("msisdnCV=" + msisdnCv);
		Logger.getRootLogger().debug("contraCV=" + contraCv);

		final Iterator<CBaseType> iter = CIdentificationList.getInstances().iterator();
		while (iter.hasNext()) {
			final CIdentification contract = (CIdentification) iter.next();
			final int cv = contract.getCv();
			if (cv == msisdnCv) {
				// do nothing
			} else if (cv == contraCv) {
				final CIdentification msisdn = findCounterPart(contract);
				final BCustomer customer = new BCustomer(contract, msisdn);
				customer.print("CUSTOMER");
			} else {
				contract.print("UNKNOWN");
			}

		}
	}

	private CIdentification findCounterPart(final CIdentification contract) {
		/*
		 * if (contract.getCv() == contraCv) { // find the oposite msisdn ident
		 * CIdentification msisdn; msisdn = (CIdentification) get(contract.getId() +
		 * 2); if (msisdn != null && msisdn.getCv() == msisdnCv) { final BCustomer
		 * customer = new BCustomer(contract, msisdn);
		 * customer.print("constumer1"); continue; } msisdn = (CIdentification)
		 * get(contract.getId() - 2); if (msisdn != null && msisdn.getCv() ==
		 * msisdnCv) { final BCustomer customer = new BCustomer(contract, msisdn);
		 * customer.print("constumer2"); continue; }
		 */
		return null;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#getPrintDescription()
	 */
	@Override
	public String getPrintDescription() {
		return "# Liste aller Kunden (Contract + MSISDN)";
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#getPrintHeader(java.lang.String)
	 */
	@Override
	public String getPrintHeader(final String prefix) {
		// TODO Auto-generated method stub
		return "";
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#getQueryString()
	 */
	@Override
	protected String getQueryString() {
		return null;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#HandleQueryResult(java.sql.ResultSet)
	 */
	@Override
	protected void HandleQueryResult(final ResultSet rs) throws SQLException {
		// do nothing
	}

}
