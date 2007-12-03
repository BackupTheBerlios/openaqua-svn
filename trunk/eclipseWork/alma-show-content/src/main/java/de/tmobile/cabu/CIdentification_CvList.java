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
public class CIdentification_CvList extends CBaseList {
	private static CIdentification_CvList INSTANCE = new CIdentification_CvList();

	public static CIdentification_CvList getInstances() {
		return INSTANCE;
	}

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
		return CIdentification_Cv.getPrintHeader(prefix);
	}

	@Override
	protected String getQueryString() {
		return "select identification_cv, description_id, sorting, valid from acm_schema.acm$ta_identification_cv ";
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
			store(new CIdentification_Cv(id, descId, sorting, valid));
		}

	}

}
