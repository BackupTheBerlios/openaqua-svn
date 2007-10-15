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

	public void RandleQueryResult(ResultSet rs) throws SQLException {
		while (rs.next()) {
			store(new CCareDescription(rs.getInt(1), 0, null, null, rs.getString(2)));
		}
	}
}

	

