/**
 * 
 */
package de.tmobile.cabu;


import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;


/**
 * @author behrenan
 * 
 */
public abstract class BaseListTemplates extends BaseList {


	@Override
	protected void HandleQueryResult(final ResultSet rs) throws SQLException {
		while (rs.next()) {
			final int id = rs.getInt(1);
			final int type = rs.getInt(2);
			final int subtype = rs.getInt(3);
			final int datatype = rs.getInt(4);
			final int unittype = rs.getInt(5);
			final int pareId = rs.getInt(6);
			final int rootId = rs.getInt(7);
			final int amcDescId = rs.getInt(8);
			final int constFlag = rs.getInt(9);
			final String value = rs.getString(10);
			final int objVers = rs.getInt(11);
			final Timestamp valid_from = rs.getTimestamp(12);
			final Timestamp valid_to = rs.getTimestamp(13);
			final int tmplMasterId = rs.getInt(14);
			final int tmplMasterVers = rs.getInt(15);


			final TElementTmpl tmpl = new TElementTmpl(id, objVers, valid_from, valid_to, type, subtype, datatype, unittype, pareId, rootId,
					amcDescId, constFlag, value, tmplMasterId, tmplMasterVers);

			put(id, tmpl);
		}
	}

	@Override
	protected void refreshList(final TTConnection connection) throws SQLException {

		//Load all Elements itself
		super.refreshList(connection);

		//Load the attribute for each element
		final int elemType = ListElementType.getInstances().getTypeId("Attribute");
		if (elemType == 0) { return; }

		final String cmd = "select element_subtype_cv, value from acm_schema.acm$ta_element_tmpl where parent_id = ? and element_type_cv="
				+ elemType;
		final PreparedStatement stmt = connection.createPreparedStatement(cmd);
		stmt.setFetchSize(20);
		for (final BaseType type : values()) {
			final TElementTmpl element = (TElementTmpl) type;
			stmt.setInt(1, element.getId());
			final ResultSet rs = stmt.executeQuery();
			while (rs.next()) {
				setAttributeType(rs.getInt(1));
				element.addAttribute(this, rs.getInt(1), rs.getString(2));
			}
			rs.close();
		}
		stmt.close();
	}

}
