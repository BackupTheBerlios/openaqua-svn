/**
 * 
 */
package de.openaqua.vwl;


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

	public int getTypeId(final String type) {
		for (final BaseType base : values()) {
			final TDataType data = (TDataType) base;
			if (data.getDescription().equals(type)) { return data.getId(); }
		}
		return 0;
	}
}