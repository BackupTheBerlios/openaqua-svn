/**
 * 
 */
package de.tmobile.cabu;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;


/**
 * @author behrenan
 * 
 */
public class CSubTypeList {

	private Map<Integer, CSubType> mapSubTypes;
	private static CSubTypeList INSTANCE = new CSubTypeList();

	public CSubTypeList() {
		super();
		this.mapSubTypes = new HashMap<Integer, CSubType>();
	}
	
	public static CSubTypeList getInstances() {
		return INSTANCE;		
	}

	public void refresh(TTConnection connection) throws SQLException {
		mapSubTypes.clear();
		if (connection.isConnected()) {
			// exec SQL command
			Statement stmt = connection.createStatement();
			ResultSet rs = stmt.executeQuery("select sub.element_subtype_cv, desc.description from acm_schema.acm$ta_element_subtype_cv sub, acm_schema.acm$ta_description desc where sub.description_id=desc.description_id");

			// parse the result
			while (rs.next()) {
				int id = rs.getInt(1);
				String value = rs.getString(2);
				mapSubTypes.put(id, new CSubType(id, value));
			}

			// close statements
			rs.close();
			stmt.close();

		}

	}

	public void list() {
		Iterator<Entry<Integer, CSubType>> it = mapSubTypes.entrySet().iterator();
		while(it.hasNext()) {
			it.next().getValue().list();
		}
	}
	
	
	public CSubType get(Integer id) {
		return mapSubTypes.get(id);
	}
}
