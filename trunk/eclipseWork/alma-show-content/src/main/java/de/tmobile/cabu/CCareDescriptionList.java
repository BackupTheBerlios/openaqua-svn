/**
 * 
 */
package de.tmobile.cabu;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Iterator;
import java.util.Map;
import java.util.TreeMap;
import java.util.Map.Entry;

/**
 * @author behrenan
 *
 */

public class CCareDescriptionList  extends CListableListObject  {


	private static CCareDescriptionList INSTANCE = new CCareDescriptionList();
	private Map<Integer, CCareDescription> mapElements = new TreeMap<Integer, CCareDescription>();

	public CCareDescriptionList() {
		super();
	}

	public static CCareDescriptionList getInstances() {
		return INSTANCE;		
	}

	
	public void clear() {
		mapElements.clear();

	}
	
	public CCareDescription get(Integer id) {
		return mapElements.get(id);
	}

	

	/* (non-Javadoc)
	 * @see de.tmobile.cabu.CListableObject#print(java.lang.String)
	 */
	@Override
	public void print(final String prefix) {
		Iterator<Entry<Integer, CCareDescription>> it = mapElements.entrySet().iterator();
		while(it.hasNext()) {
			it.next().getValue().print(prefix);
		}
		
	}
	
	
	public void refresh(TTConnection connection) throws SQLException {
		clear();
		if (connection.isConnected()) {
			// exec SQL command
			Statement stmt = connection.createStatement();
			ResultSet rs = stmt.executeQuery("select acm_description_id, acm_description from acm_schema.acm$ta_care_description");

			// parse the result
			while (rs.next()) {
				int id = rs.getInt(1);
				String value = rs.getString(2);
				mapElements.put(id, new CCareDescription(id, value));
			}

			// close statements
			rs.close();
			stmt.close();

		}
	}

	
}

	

