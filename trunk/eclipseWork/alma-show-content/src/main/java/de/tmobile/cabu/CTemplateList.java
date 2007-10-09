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
public class CTemplateList extends CElementTmplList {
	private static CTemplateList INSTANCE = new CTemplateList();
	public static CTemplateList getInstances() {
		return INSTANCE;
	}

	
	@Override
	public void print(final String prefix) {
		System.out.println("");
		System.out.println("");
		System.out.println("#Print Templates from TA_ELEMENT_TEMPL");
		System.out.println("Prefix\t\ttmplId\trootId\tparent\tmaxInst\tProRating");
		super.print(prefix);
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
				put(connection, id, new CTemplate(id));
			}

			// close statements
			rs.close();
			stmt.close();
		}
	}


}
