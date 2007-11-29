/**
 * 
 */
package de.tmobile.cabu;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Set;
import java.util.TreeSet;

/**
 * @author behrenan
 * 
 */
public class CTemplate extends CElementTmpl {
    CAttributeList attributes;

    public CTemplate(final Integer rootId) {
	super(rootId);
	attributes = new CAttributeList();
    }

    @Override
    public String getPrintLine(final String prefix) {
	String result = super.getPrintLine(prefix);
	result += getSubElements();
	return result;
    }

    public String getSubElements() {
	final Set<Integer> values = new TreeSet<Integer>();
	values.add(new Integer(14004)); // max instances
	values.add(new Integer(14005)); // ProRating Flag
	return attributes.getElementsValues(values);
    }

    @Override
    public void refresh(final TTConnection connection) throws SQLException {
	super.refresh(connection);
	setValue("");
	refreshAttributes(connection);
    }

    private void refreshAttributes(final TTConnection connection)
	    throws SQLException {
	attributes.clear();
	if (!connection.isConnected()) {
	    return;
	}

	// exec SQL command
	final Statement stmt = connection.createStatement();
	final ResultSet rs = stmt
		.executeQuery("select ELEMENT_TEMPLATE_ID from acm_schema.acm$ta_element_tmpl where root_id = parent_id and root_id="
			+ id());

	// parse the result
	while (rs.next()) {
	    final Integer id = new Integer(rs.getInt(1));
	    attributes.put(connection, id, new CAttribute(id));
	}

	// close statements
	rs.close();
	stmt.close();

    }

}
