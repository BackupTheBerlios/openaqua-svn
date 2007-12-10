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

public class ListDescription extends BaseList {
	private static final long serialVersionUID = 1056598853660288340L;
	private static ListDescription INSTANCE = new ListDescription();

	public static ListDescription getInstances() {
		return INSTANCE;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#getPrintDescription()
	 */
	@Override
	public String getPrintDescription() {
		return null;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#getPrintHeader()
	 */
	@Override
	public String getPrintHeader(final String prefix) {
		return null;
	}

	@Override
	protected String getQueryString() {
		return "select description_id, description from acm_schema.acm$ta_description";
	}

	@Override
	protected void HandleQueryResult(final ResultSet rs) throws SQLException {
		while (rs.next()) {
			put(rs.getInt(1), new TDescription(rs.getInt(1), rs.getString(2)));
		}
	}

}
