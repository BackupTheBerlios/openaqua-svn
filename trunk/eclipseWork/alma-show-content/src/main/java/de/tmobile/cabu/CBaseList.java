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
public abstract class CBaseList extends CListableObject {
	private Map mapElements = new TreeMap();

	public CBaseList() {
		super();
	}

	public void clear() {
		mapElements.clear();
	}

	public void print(String prefix) {
		Iterator it = mapElements.values().iterator();
		while (it.hasNext()) {
			((CBaseType) it.next()).print(prefix);
		}
	}

	public void store(CBaseType type) {
		mapElements.put(type.getIntegerId(), type);
	}
	
	public CBaseType get(int id) {
		return get(new Integer(id));
		
	}

	public CBaseType get(Integer id) {
		Object o = mapElements.get(id);
		if (o == null) return null;
		return (CBaseType)o;		
	}
	
	abstract protected void HandleQueryResult(ResultSet rs) throws SQLException;
	abstract public void refresh(TTConnection connection, final String query) throws SQLException;

	protected void refreshList(TTConnection connection, final String query) throws SQLException {
		clear();
		if (connection.isConnected()) {
			// exec SQL command
			Statement stmt = connection.createStatement();
			ResultSet rs = stmt.executeQuery(query);
			HandleQueryResult(rs);
			rs.close();
			stmt.close();

		}
	}

}
