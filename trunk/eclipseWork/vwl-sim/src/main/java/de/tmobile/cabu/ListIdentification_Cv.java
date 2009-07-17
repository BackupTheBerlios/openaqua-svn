/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class ListIdentification_Cv extends BaseListAlmaDataType {
	private static final long serialVersionUID = 3445018394910148226L;
	private static ListIdentification_Cv INSTANCE = new ListIdentification_Cv();

	public static ListIdentification_Cv getInstances() {
		return INSTANCE;
	}

	public int getContractidTypeId() {
		return getTypeId("contract");
	}

	public int getMasterTemplateIdTypeId() {
		return getTypeId("master");
	}

	public int getMsisdnTypeId() {
		return getTypeId("msisdn");
	}

	@Override
	protected String getQueryString() {
		return "select identification_cv, description_id, sorting, valid from acm_schema.acm$ta_identification_cv ";
	}

	public int getTemplateIdTypeId() {
		return getTypeId("template");
	}

	private int getTypeId(final String type) {
		final String low = type.toLowerCase();
		for (final BaseType base : values()) {
			final String desc = ((TDataType) base).getDescription().toLowerCase();
			if (desc.contains(low)) { return base.getId(); }
		}
		return 0;
	}

}
