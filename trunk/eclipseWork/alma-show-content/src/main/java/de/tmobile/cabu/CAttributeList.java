/**
 * 
 */
package de.tmobile.cabu;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

/**
 * @author behrenan
 *
 */
public class CAttributeList extends CElementTmplList {
	public CAttributeList() {
		super();
	}
	
	public void refresh(TTConnection connection) throws SQLException {
		clear();

		if (connection.isConnected()) {
			// exec SQL command
			Statement stmt = connection.createStatement();
			ResultSet rs = stmt
					.executeQuery("select ELEMENT_TEMPLATE_ID from ACM_SCHEMA.ACM$TA_ELEMENT_TMPL where element_template_id = root_id order by ELEMENT_TEMPLATE_ID ; ");

			// parse the result
			while (rs.next()) {
				int id = rs.getInt(1);
				put(connection, id, new CAttribute(id));
			}

			// close statements
			rs.close();
			stmt.close();
		}
	}
	

	public String toString() {
		return null;
	}
	
}
