/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class CSubTypeList extends CAlmaDataTypeBaseList {
	private static final long serialVersionUID = 1056598853660288343L;
	private static CSubTypeList INSTANCE = new CSubTypeList();

	public static CSubTypeList getInstances() {
		return INSTANCE;
	}

	@Override
	protected String getQueryString() {
		return "select element_subtype_cv, description_id, sorting, valid from acm_schema.acm$ta_element_subtype_cv";
	}
}