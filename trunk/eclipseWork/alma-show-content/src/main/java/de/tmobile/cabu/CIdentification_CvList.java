/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class CIdentification_CvList extends CAlmaDataTypeBaseList {
	private static final long serialVersionUID = 3445018394910148226L;
	private static CIdentification_CvList INSTANCE = new CIdentification_CvList();

	public static CIdentification_CvList getInstances() {
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
		for (final CBaseType base : values()) {
			final String desc = ((CAlmaDataType) base).getDescription().toLowerCase();
			if (desc.contains(low)) { return base.getId(); }
		}
		return 0;
	}

}
