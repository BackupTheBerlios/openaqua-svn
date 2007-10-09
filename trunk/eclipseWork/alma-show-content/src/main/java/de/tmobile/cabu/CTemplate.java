/**
 * 
 */
package de.tmobile.cabu;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Set;
import org.apache.log4j.Logger;

/**
 * @author behrenan
 * 
 */
public class CTemplate extends CElementTmpl {
	CAttributeList attributes;

	private Logger logger = Logger.getRootLogger();

	public CTemplate(Integer rootId) {
		super(rootId);
		attributes = new CAttributeList();
	}

	public void clearAttributes() {
		attributes.clear();
	}

	public void addAttribute(CAttribute attribute) {
	}

	public void list(String type, Integer spaces) {
		//System.out.println("");
		
		//super.list("TEMPLATE", spaces);
		//attributes.list("ATTR", spaces+1);
		
	}

	private void refreshAttributes(TTConnection connection) throws SQLException {
		clearAttributes();

		// exec SQL command
		Statement stmt = connection.createStatement();
		ResultSet rs = stmt
				.executeQuery("select ELEMENT_TEMPLATE_ID from acm_schema.acm$ta_element_tmpl where root_id = parent_id and root_id=" + id());

		// parse the result
		while (rs.next()) {
			int id = rs.getInt(1);
			//logger.debug("Add Attribute with ID "+id);
			attributes.put(connection, id, new CAttribute(id));
		}

		// close statements
		rs.close();
		stmt.close();
		
	}
	
	public void refresh(TTConnection connection) throws SQLException {
		if (!connection.isConnected())
			return;
		logger.debug("Refresh Template rootId " + id());
		super.refresh(connection);
		setValue("");
		refreshAttributes(connection);
	}
	
	public void collectElementTmplSubTypes(Set<Integer> ids) {
		super.collectElementTmplSubTypes(ids);
		attributes.collectElementTmplSubTypes(ids);
	}
	
	public void listFormated(Set<Integer> attributeTypes, String line) {
		super.listFormated(attributeTypes, line);
	}
	
}
