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
public class CSubTypeList extends CListableObject  {


	private static CSubTypeList INSTANCE = new CSubTypeList();
	private Map<Integer, CSubType> mapElements = new TreeMap<Integer, CSubType>();

	public CSubTypeList() {
		super();
	}

	public static CSubTypeList getInstances() {
		return INSTANCE;		
	}

	
	public void clear() {
		mapElements.clear();

	}
	
	public CSubType get(Integer id) {
		return mapElements.get(id);
	}

	

	/* (non-Javadoc)
	 * @see de.tmobile.cabu.CListableObject#print(java.lang.String)
	 */
	@Override
	public void print(final String prefix) {
		Iterator<Entry<Integer, CSubType>> it = mapElements.entrySet().iterator();
		while(it.hasNext()) {
			it.next().getValue().print(prefix);
		}
		
	}
	
	
	public void refresh(TTConnection connection) throws SQLException {
		clear();
		if (connection.isConnected()) {
			// exec SQL command
			Statement stmt = connection.createStatement();
			ResultSet rs = stmt.executeQuery("select sub.element_subtype_cv, desc.description from acm_schema.acm$ta_element_subtype_cv sub, acm_schema.acm$ta_description desc where sub.description_id=desc.description_id");

			// parse the result
			while (rs.next()) {
				int id = rs.getInt(1);
				String value = rs.getString(2);
				//logger.debug("Add SubType id="+id+" value="+value);
				mapElements.put(id, new CSubType(id, value));
			}

			// close statements
			rs.close();
			stmt.close();

		}

	}


	
}
