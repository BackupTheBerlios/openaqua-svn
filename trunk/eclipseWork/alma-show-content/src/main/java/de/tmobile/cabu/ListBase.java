/**
 * 
 */
package de.tmobile.cabu;


import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.TreeMap;


/**
 * @author behrenan
 * 
 */
public abstract class BaseList extends TreeMap<Integer, CBaseType> {

	public CBaseList() {
		super();
	}

	abstract public String getPrintDescription();

	abstract public String getPrintHeader(final String prefix);

	abstract protected String getQueryString();

	abstract protected void HandleQueryResult(ResultSet rs) throws SQLException;


	final public void print(final String prefix) {
		final String desc = getPrintDescription();
		final String head = getPrintHeader(prefix);

		if (desc != null && desc.length() > 0) {
			Logger.getRootLogger().emptyLine();
			Logger.getRootLogger().out(desc);
		}

		if (head != null && head.length() > 0) {
			Logger.getRootLogger().emptyLine();
			Logger.getRootLogger().out(head);
		}
		printElements(prefix);
	}

	final public void printElements(final String prefix) {
		for (final CBaseType type : values()) {
			Logger.getRootLogger().out(type.getPrintString(prefix));
		}
	}

	final protected void refreshList() throws SQLException {
		if (Configuration.getInstance().isError()) { return; }
		if (getQueryString() == null) { return; }
		clear();

		// exec SQL command
		final Statement stmt = Configuration.getInstance().getConnection().createStatement();
		final ResultSet rs = stmt.executeQuery(getQueryString());
		HandleQueryResult(rs);
		rs.close();
		stmt.close();
	}


	/**
	 * @param error
	 *           the error to set
	 */

	final public void store(final CBaseType type) {
		put(type.getId(), type);
	}
}
