/**
 * 
 */
package de.tmobile.cabu;


import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;


/**
 * @author behrenan
 * 
 */
public class ListElement extends BaseList {
	private static final long serialVersionUID = -8580341561632406783L;
	private static ListElement INSTANCE = new ListElement();

	public static ListElement getInstances() {
		return INSTANCE;
	}

	public ListElement() {
		super();
	}

	@Override
	public String getPrintDescription() {
		return null;
	}

	@Override
	public String getPrintHeader(final String prefix) {
		return null;
	}

	@Override
	protected String getQueryString() {
		return "select element_id, elem_tmpl_id, elem_tmpl_objvers, element_type_cv, element_subtype_cv, data_type_cv, unit_cv, parent_id, "
				+ " root_id, insert_time, value from acm_schema.acm$ta_element where parent_id is null";
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
		}
	}


}
