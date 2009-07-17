/**
 * 
 */
package de.openaqua.vwl;


import java.sql.ResultSet;
import java.sql.SQLException;


/**
 * @author behrenan
 * 
 */
public class BaseListAlmaDataType extends BaseList {
	private static final long serialVersionUID = 1056598853660288341L;

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#getPrintDescription()
	 */
	@Override
	public String getPrintDescription() {
		return null;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#getPrintHeader()
	 */
	@Override
	public String getPrintHeader(final String prefix) {
		return TDataType.getPrintHeader(this, prefix);
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
		final BaseType type = get(id);
		if (type instanceof TDataType) {
			return ((TDataType) type).getDescription();
		} else {
			return "unkownType";
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
			put(id, new TDataType(id, descId, sorting, valid));
		}

	}

}
