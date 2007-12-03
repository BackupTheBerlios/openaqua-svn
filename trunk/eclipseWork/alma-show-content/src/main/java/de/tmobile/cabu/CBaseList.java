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
public abstract class CBaseList extends CListableObject implements Runnable {
	private final Map<Integer, CBaseType> mapElements = new TreeMap<Integer, CBaseType>();

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

	abstract public String getPrintDescription();

	abstract public String getPrintHeader(final String prefix);

	abstract protected String getQueryString();

	abstract protected void HandleQueryResult(ResultSet rs) throws SQLException;

	@Override
	public void print(final String prefix) {
		Logger.getRootLogger().emptyLine();
		Logger.getRootLogger().out(getPrintDescription());
		Logger.getRootLogger().emptyLine();
		Logger.getRootLogger().out(getPrintHeader(prefix));
		final Iterator<CBaseType> it = mapElements.values().iterator();
		while (it.hasNext()) {
			it.next().print(prefix);
		}
	}

	protected void refreshList(final TTConnection connection) throws SQLException {
		if (Configuration.getInstance().isError()) { return; }
		clear();
		if (getQueryString() == null) { return; }

		// exec SQL command
		final Statement stmt = connection.createStatement();
		final ResultSet rs = stmt.executeQuery(getQueryString());
		HandleQueryResult(rs);
		rs.close();
		stmt.close();
	}

	public void run() {
		if (Configuration.getInstance().isError()) { return; }
		try {
			refreshList(Configuration.getInstance().getConnection());
		} catch (final SQLException e) {
			Configuration.getInstance().getConnection().reportSQLException(e);
			Configuration.getInstance().getConnection().Disconnect();
		}
	}

	/**
	 * @param error
	 *           the error to set
	 */

	public void store(final CBaseType type) {
		mapElements.put(type.getIntegerId(), type);
	}

}
