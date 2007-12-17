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
public abstract class BaseListElement extends BaseList {


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

	@Override
	protected void refreshList(final TTConnection connection) throws SQLException {

		//Load all Elements itself
		super.refreshList(connection);

		//Load the attribute for each element
		final int elemType = ListElementType.getInstances().getTypeId("Attribute");
		if (elemType == 0) { return; }

		final String cmd = "select element_subtype_cv, value from acm_schema.acm$ta_element where parent_id = ? and element_type_cv="
				+ elemType;

		final PreparedStatement stmt = connection.createPreparedStatement(cmd);
		//stmt.setFetchSize(10);
		final PerfMonitor monitor = new PerfMonitor();
		for (final BaseType type : values()) {
			final TElement element = (TElement) type;
			monitor.begin();
			stmt.setInt(1, element.getId());
			monitor.endPrep();
			final ResultSet rs = stmt.executeQuery();
			monitor.endQuery();
			//CLogger.getRootLogger().info(this.getClass().getCanonicalName() + " query: " + monitor.ouput());
			while (rs.next()) {
				setAttributeType(rs.getInt(1));
				element.addAttribute(this, rs.getInt(1), rs.getString(2));
				monitor.increase();
			}
			monitor.endResult();
			CLogger.getRootLogger().info(this.getClass().getCanonicalName() + monitor.getConsumedTime());
			rs.close();
		}
		stmt.close();

	}
}
