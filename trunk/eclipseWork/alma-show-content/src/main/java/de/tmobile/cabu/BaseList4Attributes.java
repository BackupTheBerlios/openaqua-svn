/**
 * 
 */
package de.tmobile.cabu;


import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;


/**
 * @author behrenan
 * 
 */
public abstract class BaseList4Attributes extends BaseList {

	abstract String getAttributeQueryString();

	@Override
	protected void refreshList(final TTConnection connection) throws SQLException {

		//Load all Elements itself
		super.refreshList(connection);

		//Load the attribute for each element
		final int elemType = ListElementType.getInstances().getTypeId("Attribute");
		if (elemType == 0) { return; }

		final PerfMonitor perfMonitor = new PerfMonitor();
		perfMonitor.begin();

		final PreparedStatement stmt = connection.createPreparedStatement(getAttributeQueryString());
		perfMonitor.endPrep();
		perfMonitor.endQuery();
		for (final BaseType type : values()) {
			final BaseElement element = (BaseElement) type;
			stmt.setInt(1, element.getId());
			final ResultSet rs = stmt.executeQuery();
			while (rs.next()) {
				if (rs.getInt(3) == elemType) {
					setAttributeType(rs.getInt(1));
					element.addAttribute(this, rs.getInt(1), rs.getString(2));
					perfMonitor.increase();
				}
			}
			rs.close();
		}
		perfMonitor.endResult();
		stmt.close();
		CLogger.getRootLogger().info(perfMonitor.getStatisticPrintString(getClass().getCanonicalName() + " Attr"));

	}
}
