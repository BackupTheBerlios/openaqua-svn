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

public class CCareDescriptionList  extends CBaseList  {
	private static CCareDescriptionList INSTANCE = new CCareDescriptionList();
	public static CCareDescriptionList getInstances() {
		return INSTANCE;		
	}

	protected void HandleQueryResult(ResultSet rs) throws SQLException {
		while (rs.next()) {
			store(new CCareDescription(rs.getInt(1), rs.getString(2)));
		}
	}

	protected String getQueryString() {
		return "select acm_description_id, acm_description from acm_schema.acm$ta_care_description";
	}
}

	

