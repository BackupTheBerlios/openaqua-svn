/**
 * 
 */
package de.tmobile.cabu;

import java.sql.ResultSet;
import java.sql.SQLException;

/**
 * @author behrenan
 * 
 */
public class CIdentification_TypeList extends CBaseList {

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#getPrintDescription()
	 */
	@Override
	public String getPrintDescription() {
		final String result = "# Unklar";
		return result;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#getPrintHeader()
	 */
	@Override
	public String getPrintHeader(final String prefix) {
		return CIdentification_Type.getPrintHeader(prefix);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#getQueryString()
	 */
	@Override
	protected String getQueryString() {
		return null;
	}

	public final String getTypeAsString(final int id) {
		final CBaseType type = get(id);
		if (type instanceof CIdentification_Type) {
			final CIdentification_Type i = (CIdentification_Type) type;
			return i.getDesription();
		} else {
			return "unkown";
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#HandleQueryResult(java.sql.ResultSet)
	 */
	@Override
	protected void HandleQueryResult(final ResultSet rs) throws SQLException {
		while (rs.next()) {
			final int id = rs.getInt(1);
			final int descId = rs.getInt(2);
			final int sorting = rs.getInt(3);
			final int valid = rs.getInt(4);
			store(new CIdentification_Type(id, descId, sorting, valid));
		}

	}

}
