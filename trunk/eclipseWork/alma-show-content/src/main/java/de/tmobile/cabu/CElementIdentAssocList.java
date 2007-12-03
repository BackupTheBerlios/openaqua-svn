/**
 * 
 */
package de.tmobile.cabu;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;

/**
 * @author behrenan
 * 
 */

public class CElementIdentAssocList extends CBaseList {
	private static CElementIdentAssocList INSTANCE = new CElementIdentAssocList();

	public static CElementIdentAssocList getInstances() {
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
		return CElementIdentAssoc.getPrintHeader(prefix);
	}

	@Override
	protected String getQueryString() {
		return "select identification_id, element_id, obj_version, valid_from, valid_to from acm_schema.acm$ta_element_ident_assoc order by identification_id";
	}

	@Override
	protected void HandleQueryResult(final ResultSet rs) throws SQLException {

		while (rs.next()) {
			final int id = rs.getInt(1);
			final long el = rs.getLong(2);
			final int obj = rs.getInt(3);
			final Timestamp from = rs.getTimestamp(4);
			final Timestamp to = rs.getTimestamp(5);
			store(new CElementIdentAssoc(id, el, obj, from, to));
		}
	}

}
