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
public class ListElementParentIds extends BaseList {
	private static final long serialVersionUID = -8580341561632406783L;
	private static ListElementParentIds INSTANCE = new ListElementParentIds();

	public static ListElementParentIds getInstances() {
		return INSTANCE;
	}

	public ListElementParentIds() {
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
		return "select distinct parent_id from ACM_SCHEMA.ACM$TA_ELEMENT where parent_id is not null";
	}

	@Override
	protected void HandleQueryResult(final ResultSet rs) throws SQLException {
		while (rs.next()) {
			store(new TParentId(rs.getInt(1)));
		}
	}

}
