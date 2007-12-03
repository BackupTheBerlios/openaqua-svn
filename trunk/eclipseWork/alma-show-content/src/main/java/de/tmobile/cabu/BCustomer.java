/**
 * 
 */
package de.tmobile.cabu;

/**
 * @author behrenan
 * 
 */
public class BCustomer extends CBaseType {
	private CIdentification msisdn;
	private CIdentification contract;

	public BCustomer(final CIdentification contract, final CIdentification msisdn) {
		super(0, 0, null, null);
		this.msisdn = msisdn;
		this.contract = contract;
	}

	public CIdentification getContract() {
		return contract;
	}

	public CIdentification getMsisdn() {
		return msisdn;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseType#print(java.lang.String)
	 */
	@Override
	public void print(final String prefix) {
		String result = "CUSTOMER" + sep();
		result += contract.getId() + sep();
		// result += msisdn.getId() + sep();
		result += contract.getObj_version() + sep();
		result += contract.getValid_from() + sep();
		result += contract.getValid_to() + sep();
		result += contract.getExternalIdentifier() + sep();
		// result += msisdn.getExternalIdentifier() + sep();
		Logger.getRootLogger().out(result);

	}

	public void setContract(final CIdentification contract) {
		this.contract = contract;
	}

	public void setMsisdn(final CIdentification msisdn) {
		this.msisdn = msisdn;
	}

}
