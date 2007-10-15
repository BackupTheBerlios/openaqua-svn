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




/**
 * @author behrenan
 * 
 */
public class CSubTypeList extends CListableListObject  {

	final private Logger logger=Logger.getRootLogger();
	private static CSubTypeList INSTANCE = new CSubTypeList();
	private Map mapElements = new TreeMap();

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
		return (CSubType)mapElements.get(id);
	}

	

	public void print(final String prefix) {
		Iterator it = mapElements.values().iterator();
		while(it.hasNext()) {
			CSubType sub =	(CSubType)it.next();
			sub.print(prefix);
		}
		
	}
	
	
	public void refresh(TTConnection connection) throws SQLException {
		logger.debug("Refresh SubTypeList");
		clear();
		if (connection.isConnected()) {
			// exec SQL command
			Statement stmt = connection.createStatement();
			ResultSet rs = stmt.executeQuery("select sub.element_subtype_cv, desc.description from acm_schema.acm$ta_element_subtype_cv sub, acm_schema.acm$ta_description desc where sub.description_id=desc.description_id");

			// parse the result
			while (rs.next()) {
				Integer id = new Integer(rs.getInt(1));
				String value = rs.getString(2);
				mapElements.put(id, new CSubType(id, value));
				
			}

			// close statements
			rs.close();
			stmt.close();

		}

	}


	
}
