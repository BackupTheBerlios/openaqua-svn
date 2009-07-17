/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class ListAccountsTemplates extends BaseListTemplates {
	private static final long serialVersionUID = 3445875992515527491L;
	private static ListAccountsTemplates INSTANCE = new ListAccountsTemplates();

	public static ListAccountsTemplates getInstances() {
		return INSTANCE;
	}

	public ListAccountsTemplates() {
		super();
	}


	@Override
	protected String getQueryString() {
		final int id = ListElementType.getInstances().getTypeId("Account");
		if (id != 0) {
			return "select element_template_id, element_type_cv, element_subtype_cv, data_type_cv, unit_cv, parent_id, "
					+ " root_id, acm_description_id, const_flag, value, obj_version, valid_from, valid_to, elem_mstr_tmpl_id, elem_mstr_tmpl_vers "
					+ " from acm_schema.acm$ta_element_tmpl where element_TYPE_CV=" + id;
		} else {
			return null;
		}
	}
}
