/**
 * 
 */
package de.openaqua.vwl;


/**
 * @author behrenan
 * 
 */
public class ListElementSubtype extends BaseListAlmaDataType {
	private static final long serialVersionUID = 1056598853660288339L;
	private static ListElementSubtype INSTANCE = new ListElementSubtype();

	public static ListElementSubtype getInstances() {
		return INSTANCE;
	}

	@Override
	protected String getQueryString() {
		return "select element_subtype_cv, description_id, sorting, valid from acm_schema.acm$ta_element_subtype_cv";
	}

}