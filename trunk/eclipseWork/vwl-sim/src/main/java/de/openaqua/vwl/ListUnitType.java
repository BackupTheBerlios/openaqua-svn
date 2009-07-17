/**
 * 
 */
package de.openaqua.vwl;


/**
 * @author behrenan
 * 
 */
public class ListUnitType extends BaseListAlmaDataType {
	private static final long serialVersionUID = 1056598853660288333L;
	private static ListUnitType INSTANCE = new ListUnitType();

	public static ListUnitType getInstances() {
		return INSTANCE;
	}

	@Override
	protected String getQueryString() {
		return "select unit_cv, description_id, sorting, valid from acm_schema.acm$ta_unit_cv";
	}

}