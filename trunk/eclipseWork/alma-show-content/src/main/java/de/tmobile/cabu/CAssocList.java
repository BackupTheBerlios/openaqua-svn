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
			CBaseType t = new CAssoc(rs.getInt(1), rs.getInt(3), rs.getTimestamp(4), rs.getTimestamp(5), rs.getLong(2)); 
			store(t);
		}
	}
	
	public void refresh(TTConnection connection, final String query) throws SQLException {
		refreshList(connection, "");
	}
	

}
