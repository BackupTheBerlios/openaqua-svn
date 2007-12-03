/**
 * 
 */
package de.tmobile.cabu;

/**
 * @author behrenan
 * 
 */
public class CIdentification_CvList extends CIdentification_TypeList {
	private static CIdentification_CvList INSTANCE = new CIdentification_CvList();

	public static CIdentification_CvList getInstances() {
		return INSTANCE;
	}

	@Override
	protected String getQueryString() {
		return "select identification_cv, description_id, sorting, valid from acm_schema.acm$ta_identification_cv ";
	}

}
