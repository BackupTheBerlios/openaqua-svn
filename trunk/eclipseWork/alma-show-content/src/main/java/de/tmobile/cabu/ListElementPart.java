package de.tmobile.cabu;


import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;


/**
 * @author behrenan
 * 
 */
public class ListElementPart extends BaseListElement {
	private static final long serialVersionUID = 2020240411740063048L;


	public ListElementPart(final int parentId, final BaseElement parent) {
		super(parentId, parent);
	}


	@Override
	protected String getQueryString() {
		return "select element_id, elem_tmpl_id, elem_tmpl_objvers, element_type_cv, element_subtype_cv, data_type_cv, unit_cv, parent_id, "
				+ " root_id, insert_time, value from acm_schema.acm$ta_element";

		//if (getParentId() == 0) {
		//	return "select element_id, elem_tmpl_id, elem_tmpl_objvers, element_type_cv, element_subtype_cv, data_type_cv, unit_cv, parent_id, "
		//			+ " root_id, insert_time, value " + " from acm_schema.acm$ta_element where parent_id is null";
		//} else {
		//	return "select element_id, elem_tmpl_id, elem_tmpl_objvers, element_type_cv, element_subtype_cv, data_type_cv, unit_cv, parent_id, "
		//			+ " root_id, insert_time, value " + " from acm_schema.acm$ta_element where parent_id=" + getParentId();
		//}
	}


	@Override
	protected void HandleQueryResult(final ResultSet rs) throws SQLException {
		while (rs.next()) {
			final int id = rs.getInt(1);
			final int tmplId = rs.getInt(2);
			final int tmplVers = rs.getInt(3);
			final int type = rs.getInt(4);
			final int subtype = rs.getInt(5);
			final int datatype = rs.getInt(6);
			final int unittype = rs.getInt(7);
			final int pareId = rs.getInt(8);
			final int rootId = rs.getInt(9);
			final Timestamp insert_time = rs.getTimestamp(10);
			final String value = rs.getString(11);

			final TElement elem = new TElement(id, type, subtype, datatype, unittype, pareId, rootId, value, insert_time, tmplId, tmplVers);

			put(id, elem);

			if (getParent() != null) {
				getParent().addAttribute(subtype, value);
			}


		}
	}
}
