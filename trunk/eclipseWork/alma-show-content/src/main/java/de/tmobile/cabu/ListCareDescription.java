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

public class ListCareDescription extends BaseList {
	/**
	 * 
	 */
	private static final long serialVersionUID = 5164937814421591528L;
	private static ListCareDescription INSTANCE = new ListCareDescription();

	public static ListCareDescription getInstances() {
		return INSTANCE;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#getPrintDescription()
	 */
	@Override
	public String getPrintDescription() {
		return "#Echtnamen von Bundles";
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#getPrintHeader()
	 */
	@Override
	public String getPrintHeader(final String prefix) {
		return TCareDescription.getPrintHeader(prefix);
	}

	@Override
	protected String getQueryString() {
		return "select acm_description_id, acm_description from acm_schema.acm$ta_care_description";
	}

	@Override
	protected void HandleQueryResult(final ResultSet rs) throws SQLException {
		while (rs.next()) {
			put(rs.getInt(1), new TCareDescription(rs.getInt(1), rs.getString(2)));
		}
	}
}
