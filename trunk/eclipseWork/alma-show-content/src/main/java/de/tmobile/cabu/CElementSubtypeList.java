/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class CElementSubtypeList extends CAlmaDataTypeBaseList {
	private static final long serialVersionUID = 1056598853660288339L;
	private static CElementSubtypeList INSTANCE = new CElementSubtypeList();

	public static CElementSubtypeList getInstances() {
		return INSTANCE;
	}

	@Override
	protected String getQueryString() {
		return "select element_subtype_cv, description_id, sorting, valid from acm_schema.acm$ta_element_subtype_cv";
	}

}