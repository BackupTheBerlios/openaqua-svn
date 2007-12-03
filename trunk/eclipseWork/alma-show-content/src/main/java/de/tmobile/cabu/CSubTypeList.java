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
public class CSubTypeList extends CBaseList {

	private static CSubTypeList INSTANCE = new CSubTypeList();

	public static CSubTypeList getInstances() {
		return INSTANCE;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#getPrintDescription()
	 */
	@Override
	public String getPrintDescription() {
		// TODO Auto-generated method stub
		return "";
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#getPrintHeader()
	 */
	@Override
	public String getPrintHeader(final String prefix) {
		// TODO Auto-generated method stub
		return "";
	}

	@Override
	protected String getQueryString() {
		return "select sub.element_subtype_cv, desc.description from acm_schema.acm$ta_element_subtype_cv sub, acm_schema.acm$ta_description desc where sub.description_id=desc.description_id";
	}

	@Override
	protected void HandleQueryResult(final ResultSet rs) throws SQLException {
		while (rs.next()) {
			store(new CSubType(rs.getInt(1), rs.getString(2)));
		}
	}

}