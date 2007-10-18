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

public class CDescriptionList  extends CBaseList  {
	private static CDescriptionList INSTANCE = new CDescriptionList();
	public static CDescriptionList getInstances() {
		return INSTANCE;		
	}

	protected void HandleQueryResult(ResultSet rs) throws SQLException {
		while (rs.next()) {
			store (new CDescription(rs.getInt(1),  rs.getString(2)));
		}
	}

	protected String getQueryString() {
		return "select description_id, description from acm_schema.acm$ta_description";
	}
	
}

	

