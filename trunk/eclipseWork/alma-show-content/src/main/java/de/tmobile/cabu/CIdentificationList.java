/**
 * 
 */
package de.tmobile.cabu;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Map;
import java.util.TreeMap;




/**
 * @author behrenan
 *
 */
public class CIdentificationList extends CListableListObject  {
	private Map mapElements = new TreeMap();
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
				ident.setIDENTIFICATION_TY(rs.getInt(2));
				ident.setIDENTIFICATION_CV(rs.getInt(3));
				ident.setMANDATOR_ID(rs.getInt(4));
				ident.setELEMENT_TEMPLATE_ID(rs.getInt(5));
				ident.setELEMENT_MASTER_TEMPLATE_ID(rs.getInt(6));
				ident.setEXTERNAL_IDENTIFIER(rs.getString(7));
				ident.setOBJ_VERSION(rs.getInt(8));
				ident.setVALID_FROM(rs.getDate(9).toString(),rs.getTime(9).toString());
				//ident.setVALID_TO(rs.getDate(10).toString(), rs.getTime(10).toString());
				mapElements.put(new Integer (ident.getIDENTIFICATION_ID()), ident);
			}

			// close statements
			rs.close();
			stmt.close();

		}

	}
	
	public void print(String prefix) {
		/*
		Iterator<Entry<Integer, CIdentification>> it = mapElements.entrySet().iterator();
		while(it.hasNext()) {
			it.next().getValue().print(prefix);
		}
		*/
	}

	public void clear() {
		mapElements.clear();
	}

}
