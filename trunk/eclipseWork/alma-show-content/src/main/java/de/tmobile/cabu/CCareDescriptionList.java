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

public class CCareDescriptionList extends CBaseList {
	private static CCareDescriptionList INSTANCE = new CCareDescriptionList();

	public static CCareDescriptionList getInstances() {
		return INSTANCE;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#getPrintDescription()
	 */
	@Override
	public String getPrintDescription() {
		// TODO Auto-generated method stub
		return "";
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#getPrintHeader()
	 */
	@Override
	public String getPrintHeader(final String prefix) {
		// TODO Auto-generated method stub
		return "";
	}

	@Override
	protected String getQueryString() {
		return "select acm_description_id, acm_description from acm_schema.acm$ta_care_description";
	}

	@Override
	protected void HandleQueryResult(final ResultSet rs) throws SQLException {
		while (rs.next()) {
			store(new CCareDescription(rs.getInt(1), rs.getString(2)));
		}
	}
}
