/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class ListCounterSets extends BaseListElement {
	private static final long serialVersionUID = 1468504050251809198L;
	private static ListCounterSets INSTANCE = new ListCounterSets();

	public static ListCounterSets getInstances() {
		return INSTANCE;
	}

	public ListCounterSets() {
		super();
	}


	@Override
	protected String getQueryString() {
		final int id = ListElementType.getInstances().getTypeId("Counter Set");
		if (id != 0) {
			return "select element_id, elem_tmpl_id, elem_tmpl_objvers, element_type_cv, element_subtype_cv, data_type_cv, unit_cv, parent_id, "
					+ " root_id, insert_time, value from acm_schema.acm$ta_element where element_TYPE_CV=" + id;
		} else {
			return null;
		}
	}

}
