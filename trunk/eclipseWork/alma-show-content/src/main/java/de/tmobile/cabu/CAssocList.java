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

public class CAssocList  extends CBaseList  {
	private static CAssocList INSTANCE = new CAssocList();
	public static CAssocList getInstances() {
		return INSTANCE;		
	}
	
	
	public void HandleQueryResult(ResultSet rs) throws SQLException {
		while (rs.next()) {
			store(new CAssoc(rs.getInt(1), rs.getInt(2), rs.getTimestamp(3), rs.getTimestamp(4), rs.getLong(5)));
		}
	}

	protected String getQueryString() {
		return "select identification_id, obj_version, valid_from, valid_to, element_Id from acm_schema.acm$ta_element_ident_assoc";
	}
}
