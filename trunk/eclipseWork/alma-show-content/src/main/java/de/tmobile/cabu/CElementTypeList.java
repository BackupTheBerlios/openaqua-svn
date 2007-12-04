/**
 * 
 */
package de.tmobile.cabu;

/**
 * @author behrenan
 * 
 */
public class CElementTypeList extends CAlmaDataTypeBaseList {

	private static CElementTypeList INSTANCE = new CElementTypeList();

	public static CElementTypeList getInstances() {
		return INSTANCE;
	}

	@Override
	protected String getQueryString() {
		return "select element_type_cv, description_id, sorting, valid from acm_schema.acm$ta_element_type_cv";
	}

}