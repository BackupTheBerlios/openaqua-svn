/**
 * 
 */
package de.tmobile.cabu;


import java.sql.ResultSet;
import java.sql.SQLException;


/**
 * @author behrenan
 * 
 */
public class ListElementRootIds extends BaseList {
	private static final long serialVersionUID = -8580311561632406783L;
	private static ListElementRootIds INSTANCE = new ListElementRootIds();

	public static ListElementRootIds getInstances() {
		return INSTANCE;
	}

	public ListElementRootIds() {
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
		return "select distinct root_id from ACM_SCHEMA.ACM$TA_ELEMENT where root_id is not null";
	}

	@Override
	protected void HandleQueryResult(final ResultSet rs) throws SQLException {
		while (rs.next()) {
			put(rs.getInt(1), new TRootId(rs.getInt(1)));
		}
	}
}
