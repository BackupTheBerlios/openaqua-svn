/**
 * 
 */
package de.tmobile.cabu;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Iterator;
import java.util.Set;
import java.util.TreeSet;

/**
 * @author behrenan
 * 
 */
public class CTemplateList extends CElementTmplList {

	private static CTemplateList INSTANCE = new CTemplateList();
	public static CTemplateList getInstances() {
		return INSTANCE;
	}


	public void list(String type, Integer spaces) {
		System.out.println("# Print Templates from TA_ELEMENT_TEMPL");
		
		//list known attributes
		Set<Integer> attributeTypes = new TreeSet<Integer>();
		collectElementTmplSubTypes(attributeTypes);
		Iterator<Integer> ait = attributeTypes.iterator();
		String header="";
		while(ait.hasNext()) {
			Integer i = ait.next();
			CSubType subType = CSubTypeList.getInstances().get(i); 
			header += subType.getDescription() + sep();
		}
		//System.out.println("#"+header);
		
		
		//List Templates
		System.out.println(listHeader());
		listFormated(attributeTypes, new String());
		
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
