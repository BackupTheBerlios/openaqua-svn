/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class ListDataType extends BaseListAlmaDataType {

	/**
	 * 
	 */
	private static final long serialVersionUID = -7728760585323339579L;
	private static ListDataType INSTANCE = new ListDataType();

	public static ListDataType getInstances() {
		return INSTANCE;
	}

	@Override
	protected String getQueryString() {
		return "select data_type_cv, description_id, sorting, valid from acm_schema.acm$ta_data_type_cv";
	}

}