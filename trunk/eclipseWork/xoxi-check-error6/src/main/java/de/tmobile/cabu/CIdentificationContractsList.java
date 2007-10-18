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
public class CIdentificationContractsList extends CBaseList  {
	private static CIdentificationContractsList  INSTANCE = new CIdentificationContractsList ();
	public static CIdentificationContractsList getInstances() {
		return INSTANCE;		
	}
	


	/* (non-Javadoc)
	 * @see de.tmobile.cabu.CBaseList#HandleQueryResult(java.sql.ResultSet)
	 */
	protected void HandleQueryResult(ResultSet rs) throws SQLException {
		while (rs.next()) {
			int type = rs.getInt(5);
			int cv = rs.getInt(6);
			int mandator = rs.getInt(7);
			int elementTemplateId = rs.getInt(8);
			int elementMasterTemplateId = rs.getInt(9);
			String externalIdentifier = rs.getString(10);

			CIdentification ident = new CIdentification(rs.getInt(1), rs
					.getInt(2), rs.getTimestamp(3), rs.getTimestamp(4), type,
					cv, mandator, elementTemplateId, elementMasterTemplateId,
					externalIdentifier);
			store(ident);
		}

	}



	protected String getQueryString() {
		String command = "Select ";
		command += " id.IDENTIFICATION_ID, id.OBJ_VERSION,    	id.VALID_FROM, id.VALID_TO, ";
		command += " ty.description_id,    cv.description_id,	id.MANDATOR_ID, ";
		command += " id.ELEMENT_TEMPLATE_ID, id.ELEMENT_MASTER_TEMPLATE_ID, id.EXTERNAL_IDENTIFIER ";
		command +=" from acm_schema.acm$ta_identification id, acm_schema.acm$ta_identification_cv cv, acm_schema.acm$ta_identification_ty ty";
		command +=" where id.identification_cv=cv.identification_cv";
		command +=" and id.identification_ty=ty.identification_ty";
		command +=" and ty.description_id=41 ";
		return command;
	}

}
