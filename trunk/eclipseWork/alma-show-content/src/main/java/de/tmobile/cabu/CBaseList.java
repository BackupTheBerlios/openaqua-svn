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
public abstract class CBaseList
        extends
        CListableObject {
	private final Map<Integer, CBaseType>	mapElements	= new TreeMap<Integer, CBaseType>();


	public CBaseList() {
		super();
	}


	public void clear() {
		mapElements.clear();
	}


	public CBaseType get(final int id) {
		return get(new Integer(id));

	}


	public CBaseType get(final Integer id) {
		final Object o = mapElements.get(id);
		if (o == null) { return null; }
		return (CBaseType) o;
	}


	abstract protected String getQueryString();


	abstract protected void HandleQueryResult(ResultSet rs) throws SQLException;


	@Override
	public void print(final String prefix) {
		final Iterator<CBaseType> it = mapElements.values().iterator();
		while (it.hasNext()) {
			(it.next()).print(prefix);
		}
	}


	protected void refreshList(final TTConnection connection) throws SQLException {
		clear();
		if (connection.isConnected()) {
			// exec SQL command
			final Statement stmt = connection.createStatement();
			final ResultSet rs = stmt.executeQuery(getQueryString());
			HandleQueryResult(rs);
			rs.close();
			stmt.close();
		}
	}


	public void store(final CBaseType type) {
		mapElements.put(type.getIntegerId(), type);
	}

}
