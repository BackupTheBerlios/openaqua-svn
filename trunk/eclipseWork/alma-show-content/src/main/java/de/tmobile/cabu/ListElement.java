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
public abstract class ListElement extends BaseList {
	private static final long serialVersionUID = -8580341561632406783L;


	@Override
	public String getPrintDescription() {
		return null;
	}


	@Override
	public String getPrintHeader(final String prefix) {
		return null;
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
			elem.setOwnerList(this);
			put(id, elem);
			//Thread.yield();
		}
	}


	@Override
	protected void refreshList() throws SQLException {
		super.refreshList();
		final int elemType = ListElementType.getInstances().getTypeId("Attribute");
		if (elemType == 0) { return; }

		final String cmd = "select element_subtype_cv, value from acm_schema.acm$ta_element where parent_id = ? and element_type_cv="
				+ elemType;

		final PreparedStatement stmt = CConfiguration.getInstance().getConnection().createPreparedStatement(cmd);
		stmt.setFetchSize(20);

		for (final BaseType type : values()) {
			final TElement element = (TElement) type;

			stmt.setInt(1, element.getId());
			final ResultSet rs = stmt.executeQuery();
			//CLogger.getRootLogger().debug(element.getPrintString("ELEMENT="));
			while (rs.next()) {
				//CLogger.getRootLogger().debug("Add Attribute type=" + rs.getInt(1) + " value=" + rs.getString(2));
				element.addAttribute(this, rs.getInt(1), rs.getString(2));
			}
			//CLogger.getRootLogger().debug(element.getPrintString("ELEMENT="));
			rs.close();

			Thread.yield();
		}
		stmt.close();
	}


}
