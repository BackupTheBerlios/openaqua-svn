/**
 * 
 */
package de.openaqua.vwl;


import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;


/**
 * @author behrenan
 * 
 */
public abstract class BaseList extends TreeMap<Integer, BaseType> {
	private final Set<Integer> knownAttributes = new TreeSet<Integer>();

	protected BaseList() {
		super();
	}


	public Set<Integer> getAttributeTypes() {
		return knownAttributes;
	}

	public String getPrintDescription() {
		return null;
	}


	public abstract String getPrintHeader(final String prefix);

	abstract protected String getQueryString();


	abstract protected void HandleQueryResult(ResultSet rs) throws SQLException;

	public void print(final String prefix) {
		for (final BaseType base : values()) {
			CLogger.getRootLogger().out(base.getPrintString(knownAttributes, prefix));
		}
	}


	protected void refreshList(final TTConnection connection) throws SQLException {
		if (!connection.isConnected()) { return; }
		if (getQueryString() == null) { return; }
		clear(); //remove old content

		// exec SQL command
		final PerfMonitor perfMonitor = new PerfMonitor();
		perfMonitor.begin();
		final Statement stmt = connection.createStatement();
		perfMonitor.endPrep();
		final ResultSet rs = stmt.executeQuery(getQueryString());
		perfMonitor.endQuery();

		//handle result
		HandleQueryResult(rs);
		perfMonitor.endResult();
		perfMonitor.setCounter(size());

		//clean up
		rs.close();
		stmt.close();

		CLogger.getRootLogger().info(perfMonitor.getStatisticPrintString(getClass().getCanonicalName()));
	}

	public void setAttributeType(final int typeAttribute) {
		if (!knownAttributes.contains(typeAttribute)) {
			knownAttributes.add(typeAttribute);
		}
	}

}
