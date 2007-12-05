/**
 * 
 */
package de.tmobile.cabu;


import java.util.Iterator;


/**
 * @author behrenan
 * 
 */
public class CIdentification_CvList extends CAlmaDataTypeBaseList {
	private static CIdentification_CvList INSTANCE = new CIdentification_CvList();

	public static CIdentification_CvList getInstances() {
		return INSTANCE;
	}

	public int getContractidTypeId() {
		final Iterator<CBaseType> iter = iterator();
		while (iter.hasNext()) {
			final CAlmaDataType type = (CAlmaDataType) iter.next();
			final String desc = type.getDescription().toLowerCase();
			if (desc.contains("contract")) { return type.getId(); }
		}
		return 0;
	}

	public int getMasterTemplateIdTypeId() {
		final Iterator<CBaseType> iter = iterator();
		while (iter.hasNext()) {
			final CAlmaDataType type = (CAlmaDataType) iter.next();
			final String desc = type.getDescription().toLowerCase();
			if (desc.contains("master")) { return type.getId(); }
		}
		return 0;
	}

	public int getMsisdnTypeId() {
		final Iterator<CBaseType> iter = iterator();
		while (iter.hasNext()) {
			final CAlmaDataType type = (CAlmaDataType) iter.next();
			final String desc = type.getDescription().toLowerCase();
			if (desc.contains("msisdn")) { return type.getId(); }
		}
		return 0;
	}

	@Override
	protected String getQueryString() {
		return "select identification_cv, description_id, sorting, valid from acm_schema.acm$ta_identification_cv ";
	}

	public int getTemplateIdTypeId() {
		final Iterator<CBaseType> iter = iterator();
		while (iter.hasNext()) {
			final CAlmaDataType type = (CAlmaDataType) iter.next();
			final String desc = type.getDescription().toLowerCase();
			if (desc.contains("template")) { return type.getId(); }
		}
		return 0;
	}

}
