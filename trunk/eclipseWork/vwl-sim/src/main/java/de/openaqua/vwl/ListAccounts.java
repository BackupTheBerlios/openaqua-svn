/**
 * 
 */
package de.openaqua.vwl;


/**
 * @author behrenan
 * 
 */
public class ListAccounts extends BaseListElement {
	private static final long serialVersionUID = 3445875992515527491L;
	private static ListAccounts INSTANCE = new ListAccounts();

	public static ListAccounts getInstances() {
		return INSTANCE;
	}

	public ListAccounts() {
		super();
	}


	@Override
	protected String getQueryString() {
		final int id = ListElementType.getInstances().getTypeId("Account");
		if (id != 0) {
			return "select element_id, elem_tmpl_id, elem_tmpl_objvers, element_type_cv, element_subtype_cv, data_type_cv, unit_cv, parent_id,  root_id, insert_time, value from acm_schema.acm$ta_element where element_TYPE_CV="
					+ id;
		} else {
			return null;
		}
	}


}
