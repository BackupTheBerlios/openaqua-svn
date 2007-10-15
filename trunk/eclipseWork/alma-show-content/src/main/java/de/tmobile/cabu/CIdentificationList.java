/**
 * 
 */
package de.tmobile.cabu;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Iterator;
import java.util.Map;
import java.util.TreeMap;




/**
 * @author behrenan
 *
 */
public class CIdentificationList extends CListableListObject  {
	private Map mapContracts = new TreeMap();
	private Map mapTemplates = new TreeMap();
	final private Logger logger = Logger.getRootLogger();
	
	private static CIdentificationList  INSTANCE = new CIdentificationList ();
	public static CIdentificationList getInstances() {
		return INSTANCE;		
	}
	
	public CIdentificationList() {
		super();
	}
	

	
	public void refresh(TTConnection connection) throws SQLException {
		logger.debug("Refresh Identifiction List");
		clear();
		if (connection.isConnected()) {
			// exec SQL command
			Statement stmt = connection.createStatement();
			String command = "Select ";
			command +=" id.IDENTIFICATION_ID, ty.description_id, cv.description_id, id.MANDATOR_ID, id.ELEMENT_TEMPLATE_ID, id.ELEMENT_MASTER_TEMPLATE_ID, id.EXTERNAL_IDENTIFIER, id.OBJ_VERSION, id.VALID_FROM, id.VALID_TO";
			command +=" from acm_schema.acm$ta_identification id, acm_schema.acm$ta_identification_cv cv, acm_schema.acm$ta_identification_ty ty";
			command +=" where id.identification_cv=cv.identification_cv";
			command +=" and id.identification_ty=ty.identification_ty";
			ResultSet rs = stmt.executeQuery(command);
			

			// parse the result
			while (rs.next()) {
				CIdentification ident = new CIdentification();
				ident.setIDENTIFICATION_ID(rs.getInt(1));
				int type = rs.getInt(2);
				ident.setIDENTIFICATION_TY(type);
				ident.setIDENTIFICATION_CV(rs.getInt(3));
				ident.setMANDATOR_ID(rs.getInt(4));
				ident.setELEMENT_TEMPLATE_ID(rs.getInt(5));
				ident.setELEMENT_MASTER_TEMPLATE_ID(rs.getInt(6));
				ident.setEXTERNAL_IDENTIFIER(rs.getString(7));
				ident.setOBJ_VERSION(rs.getInt(8));
				ident.setVALID_FROM(rs.getDate(9).toString(),rs.getTime(9).toString());
				if (rs.getObject(10) == null) {
					ident.setVALID_TO(null);
				} else {
					ident.setVALID_TO(rs.getDate(10).toString(), rs.getTime(10).toString());
				}
				if (type == 43) {
					mapTemplates.put(new Integer(ident.getIDENTIFICATION_ID()), ident);
				}
				if (type == 41) {
					mapContracts.put(new Integer(ident.getIDENTIFICATION_ID()), ident);
				}
			}

			// close statements
			rs.close();
			stmt.close();

		}

	}
	
	
	public void printTemplateIds(String prefix) {
		//print templates
		Iterator it = mapTemplates.values().iterator();
		while(it.hasNext()) {
			CIdentification id = (CIdentification )it.next();
			id.print(prefix);
		}
	}

	public void printContractIds(String prefix) {
		Iterator it = mapContracts.values().iterator();
		while(it.hasNext()) {
			CIdentification id = (CIdentification )it.next();
			id.print(prefix);
		}
	}
	
	public void print(String prefix) {
		printTemplateIds(prefix);
		printContractIds(prefix);
	}

	public void clear() {
		mapContracts.clear();
		mapTemplates.clear();
	}

}
