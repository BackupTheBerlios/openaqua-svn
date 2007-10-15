/**
 * 
 */
package de.tmobile.cabu;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;




/**
 * @author behrenan
 *
 */
public class CIdentificationContractsList extends CBaseList  {
	final private Logger logger = Logger.getRootLogger();
	
	private static CIdentificationContractsList  INSTANCE = new CIdentificationContractsList ();
	public static CIdentificationContractsList getInstances() {
		return INSTANCE;		
	}
	
	public CIdentificationContractsList() {
		super();
	}
	

	
	public void refresh(TTConnection connection) throws SQLException {
		logger.debug("Refresh Identifiction List");

		if (connection.isConnected()) {
			// exec SQL command
			Statement stmt = connection.createStatement();
			String command = "Select ";
			command +=" id.IDENTIFICATION_ID, ty.description_id, cv.description_id, id.MANDATOR_ID, id.ELEMENT_TEMPLATE_ID, id.ELEMENT_MASTER_TEMPLATE_ID, id.EXTERNAL_IDENTIFIER, id.OBJ_VERSION, id.VALID_FROM, id.VALID_TO";
			command +=" from acm_schema.acm$ta_identification id, acm_schema.acm$ta_identification_cv cv, acm_schema.acm$ta_identification_ty ty";
			command +=" where id.identification_cv=cv.identification_cv";
			command +=" and id.identification_ty=ty.identification_ty";
			command +=" and ty.description_id == 41 ";
			ResultSet rs = stmt.executeQuery(command);
			

			// parse the result
			while (rs.next()) {
				int type = rs.getInt(2);
				int cv = rs.getInt(3);
				int mandator=rs.getInt(4);
				int elementTemplateId = rs.getInt(5);
				int elementMasterTemplateId = rs.getInt(6);
				String externalIdentifier = rs.getString(7);
				
				CIdentification ident = new CIdentification(rs.getInt(1), rs.getInt(8), rs.getTimestamp(9), rs.getTimestamp(10), type, cv, mandator, elementTemplateId, elementMasterTemplateId, externalIdentifier);
				store(ident);
			}

			// close statements
			rs.close();
			stmt.close();

		}

	}

}
