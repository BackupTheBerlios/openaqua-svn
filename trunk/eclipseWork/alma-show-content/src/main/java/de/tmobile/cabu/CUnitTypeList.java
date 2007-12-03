/**
 * 
 */
package de.tmobile.cabu;

/**
 * @author behrenan
 * 
 */
public class CUnitTypeList extends CIdentification_TypeList {

	private static CUnitTypeList INSTANCE = new CUnitTypeList();

	public static CUnitTypeList getInstances() {
		return INSTANCE;
	}

	@Override
	protected String getQueryString() {
		return "select unit_cv, description_id, sorting, valid from acm_schema.acm$ta_unit_cv";
	}

}