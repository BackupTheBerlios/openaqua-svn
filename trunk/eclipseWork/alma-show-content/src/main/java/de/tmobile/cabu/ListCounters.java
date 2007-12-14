/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class ListCounters extends ListElement {
	private static final long serialVersionUID = -5885161573148650005L;
	private static ListCounters INSTANCE = new ListCounters();

	public static ListCounters getInstances() {
		return INSTANCE;
	}

	public ListCounters() {
		super();
	}


	@Override
	protected String getQueryString() {
		final int id = ListElementType.getInstances().getTypeId("Counter");
		if (id != 0) {
			return "select element_id, elem_tmpl_id, elem_tmpl_objvers, element_type_cv, element_subtype_cv, data_type_cv, unit_cv, parent_id, "
					+ " root_id, insert_time, value from acm_schema.acm$ta_element where element_TYPE_CV=" + id;
		} else {
			return null;
		}
	}

}
