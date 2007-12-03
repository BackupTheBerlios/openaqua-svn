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
public class CIdentificationList extends CBaseList {
	private static CIdentificationList INSTANCE = new CIdentificationList();

	public static CIdentificationList getInstances() {
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

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#getQueryString()
	 */
	@Override
	protected String getQueryString() {
		String command = "Select ";
		command += " IDENTIFICATION_ID, identification_ty, identification_cv,  ";
		command += " mandator_id, ELEMENT_TEMPLATE_ID, ELEMENT_MASTER_TEMPLATE_ID, EXTERNAL_IDENTIFIER, ";
		command += " OBJ_VERSION, VALID_FROM, VALID_TO ";
		command += " from acm_schema.acm$ta_identification";
		return command;
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
			final int ty = rs.getInt(2);
			final int cv = rs.getInt(3);
			final int mandator = rs.getInt(4);
			final int elementTemplateId = rs.getInt(5);
			final int elementMasterTemplateId = rs.getInt(6);
			final String externalIdentifier = rs.getString(7);
			final int objVer = rs.getInt(8);
			final Timestamp val_from = rs.getTimestamp(9);
			final Timestamp val_to = rs.getTimestamp(10);

			store(new CIdentification(id, objVer, val_from, val_to, ty, cv, mandator, elementTemplateId, elementMasterTemplateId,
					externalIdentifier));
		}

	}
}
