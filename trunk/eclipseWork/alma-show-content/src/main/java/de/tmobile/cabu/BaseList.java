/**
 * 
 */
package de.tmobile.cabu;


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


	public String getPrintHeader(final String prefix) {
		return null;
	}


	abstract protected String getQueryString();

	abstract protected void HandleQueryResult(ResultSet rs) throws SQLException;

	public void print(final String prefix) {
		final String desc = getPrintDescription();
		final String head = getPrintHeader(prefix);

		if (desc != null && desc.length() > 0) {
			CLogger.getRootLogger().emptyLine();
			CLogger.getRootLogger().out(desc);
		}

		if (head != null && head.length() > 0) {
			CLogger.getRootLogger().emptyLine();
			CLogger.getRootLogger().out(head);
		}
		printElements(prefix);
	}

	final public void printElements(final String prefix) {
		for (final BaseType type : values()) {
			CLogger.getRootLogger().out(type.getPrintString(prefix));
		}
	}

	protected void refreshList() throws SQLException {
		final TTConnection connection = CConfiguration.getInstance().getConnection(this);
		if (!connection.isConnected()) { return; }
		if (getQueryString() == null) { return; }


		clear(); //remove old content

		// exec SQL command
		final Statement stmt = connection.createStatement();
		final ResultSet rs = stmt.executeQuery(getQueryString());

		HandleQueryResult(rs);

		rs.close();
		stmt.close();
	}

	public void storeAttributeType(final int typeAttribute) {
		knownAttributes.add(typeAttribute);
	}

}
