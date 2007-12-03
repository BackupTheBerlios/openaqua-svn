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
public class CIdentificationContractsList extends CBaseList {
	private static CIdentificationContractsList INSTANCE = new CIdentificationContractsList();

	public static CIdentificationContractsList getInstances() {
		return INSTANCE;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#getPrintDescription()
	 */
	@Override
	public String getPrintDescription() {
		final String result = "# Liste der Verträge";
		return result;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.CBaseList#getPrintHeader()
	 */
	@Override
	public String getPrintHeader(final String prefix) {
		return CIdentification.getPrintHeader(prefix);
	}

	@Override
	protected String getQueryString() {
		String command = "Select ";
		command += " id.IDENTIFICATION_ID, id.OBJ_VERSION,    	id.VALID_FROM, id.VALID_TO, ";
		command += " ty.description_id,    cv.description_id,	id.MANDATOR_ID, ";
		command += " id.ELEMENT_TEMPLATE_ID, id.ELEMENT_MASTER_TEMPLATE_ID, id.EXTERNAL_IDENTIFIER ";
		command += " from acm_schema.acm$ta_identification id, acm_schema.acm$ta_identification_cv cv, acm_schema.acm$ta_identification_ty ty";
		command += " where id.identification_cv=cv.identification_cv";
		command += " and id.identification_ty=ty.identification_ty";
		command += " and ty.description_id=41 ";
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
			final int type = rs.getInt(5);
			final int cv = rs.getInt(6);
			final int mandator = rs.getInt(7);
			final int elementTemplateId = rs.getInt(8);
			final int elementMasterTemplateId = rs.getInt(9);
			final String externalIdentifier = rs.getString(10);

			final CIdentification ident = new CIdentification(rs.getInt(1), rs.getInt(2), rs.getTimestamp(3), rs.getTimestamp(4), type, cv,
					mandator, elementTemplateId, elementMasterTemplateId, externalIdentifier);
			store(ident);
		}

	}

}
