/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class ListElementType extends BaseListAlmaDataType {
	private static final long serialVersionUID = 1056598853660288337L;
	private static ListElementType INSTANCE = new ListElementType();

	public static ListElementType getInstances() {
		return INSTANCE;
	}

	@Override
	protected String getQueryString() {
		return "select element_type_cv, description_id, sorting, valid from acm_schema.acm$ta_element_type_cv";
	}

}