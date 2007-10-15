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

public class CDescriptionList  extends CListableListObject  {


	private static CDescriptionList INSTANCE = new CDescriptionList();
	private Map<Integer, CDescription> mapElements = new TreeMap<Integer, CDescription>();

	public CDescriptionList() {
		super();
	}

	public static CDescriptionList getInstances() {
		return INSTANCE;		
	}

	
	public void clear() {
		mapElements.clear();

	}
	
	public CDescription get(Integer id) {
		CDescription result = mapElements.get(id);
		if (result == null) {
			result = new CDescription(0, "<null>");
		}
		return result;
	}

	

	/* (non-Javadoc)
	 * @see de.tmobile.cabu.CListableObject#print(java.lang.String)
	 */
	@Override
	public void print(final String prefix) {
		Iterator<Entry<Integer, CDescription>> it = mapElements.entrySet().iterator();
		while(it.hasNext()) {
			it.next().getValue().print(prefix);
		}
		
	}
	
	
	public void refresh(TTConnection connection) throws SQLException {
		clear();
		if (connection.isConnected()) {
			// exec SQL command
			Statement stmt = connection.createStatement();
			ResultSet rs = stmt.executeQuery("select description_id, description from acm_schema.acm$ta_description");

			// parse the result
			while (rs.next()) {
				int id = rs.getInt(1);
				String value = rs.getString(2);
				mapElements.put(id, new CDescription(id, value));
			}

			// close statements
			rs.close();
			stmt.close();

		}
	}

	
}

	

