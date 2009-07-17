/**
 * 
 */
package de.openaqua.vwl;


import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;


/**
 * @author behrenan
 * 
 */

public class ListElementIdentAssoc extends BaseList {
	private static final long serialVersionUID = 1815696993834737972L;
	private static ListElementIdentAssoc INSTANCE = new ListElementIdentAssoc();

	public static ListElementIdentAssoc getInstances() {
		return INSTANCE;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#getPrintDescription()
	 */
	@Override
	public String getPrintDescription() {
		String result = "# Verbindung zwischen Elementen (Counter Instances) und Kunden\n";
		result += "# ID zeigt auf das ID element eines Vertrags, elementId auf eine CounterInstance";
		return result;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#getPrintHeader()
	 */
	@Override
	public String getPrintHeader(final String prefix) {
		return TElementIdentAssoc.getPrintHeader(this, prefix);
	}

	@Override
	protected String getQueryString() {
		return "select identification_id, element_id, obj_version, valid_from, valid_to from acm_schema.acm$ta_element_ident_assoc";
	}

	@Override
	protected void HandleQueryResult(final ResultSet rs) throws SQLException {
		int locId = 1;
		while (rs.next()) {
			final int id = rs.getInt(1);
			final long el = rs.getLong(2);
			final int obj = rs.getInt(3);
			final Timestamp from = rs.getTimestamp(4);
			final Timestamp to = rs.getTimestamp(5);
			put(locId++, new TElementIdentAssoc(id, el, obj, from, to));
		}
	}

}
