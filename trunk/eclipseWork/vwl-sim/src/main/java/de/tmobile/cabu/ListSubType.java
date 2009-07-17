/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class ListSubType extends BaseListAlmaDataType {
	private static final long serialVersionUID = 1056598853660288343L;
	private static ListSubType INSTANCE = new ListSubType();

	public static ListSubType getInstances() {
		return INSTANCE;
	}

	@Override
	protected String getQueryString() {
		return "select element_subtype_cv, description_id, sorting, valid from acm_schema.acm$ta_element_subtype_cv";
	}
}