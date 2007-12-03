/**
 * 
 */
package de.tmobile.cabu;

/**
 * @author behrenan
 * 
 */
public class CIdentification_TyList extends CIdentification_TypeList {
	private static CIdentification_TyList INSTANCE = new CIdentification_TyList();

	public static CIdentification_TyList getInstances() {
		return INSTANCE;
	}

	@Override
	protected String getQueryString() {
		return "select identification_ty, description_id, sorting, valid from acm_schema.acm$ta_identification_ty ";
	}

}
