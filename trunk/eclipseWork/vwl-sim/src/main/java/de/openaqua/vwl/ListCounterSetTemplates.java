/**
 * 
 */
package de.openaqua.vwl;


/**
 * @author behrenan
 * 
 */
public class ListCounterSetTemplates extends BaseListTemplates {
	private static final long serialVersionUID = -6748527659998733373L;
	private static ListCounterSetTemplates INSTANCE = new ListCounterSetTemplates();

	public static ListCounterSetTemplates getInstances() {
		return INSTANCE;
	}

	public ListCounterSetTemplates() {
		super();
	}


	@Override
	protected String getQueryString() {
		final int id = ListElementType.getInstances().getTypeId("Counter Set");
		if (id != 0) {
			return "select element_template_id, element_type_cv, element_subtype_cv, data_type_cv, unit_cv, parent_id, "
					+ " root_id, acm_description_id, const_flag, value, obj_version, valid_from, valid_to, elem_mstr_tmpl_id, elem_mstr_tmpl_vers "
					+ " from acm_schema.acm$ta_element_tmpl where element_TYPE_CV=" + id;
		} else {
			return null;
		}
	}

}
