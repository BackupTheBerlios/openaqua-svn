/**
 * 
 */
package de.tmobile.cabu;

import java.sql.SQLException;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

/**
 * @author behrenan
 * 
 */
public class CElementTmplList extends CListableObject {

    private final Map<Integer, CElementTmpl> mapElements = new TreeMap<Integer, CElementTmpl>();

    /*
     * (non-Javadoc)
     * 
     * @see de.tmobile.cabu.IElementList#clear()
     */
    public void clear() {
	mapElements.clear();

    }

    /*
     * (non-Javadoc)
     * 
     * @see de.tmobile.cabu.IElementList#get(java.lang.Integer)
     */
    public CElementTmpl get(final Integer id) {
	return mapElements.get(id);
    }

    public String getElementsValues(final Set values) {
	final String result = "";
	/*
	 * Iterator it = mapElements.values().iterator(); while(it.hasNext()) {
	 * CElementTmpl element = (CElementTmpl)it.next(); if
	 * (values.contains(element.getSubType().getId())) { result +=
	 * element.getValue() + sep(); } }
	 */
	return result;
    }

    @Override
    public void print(final String prefix) {
	final Iterator<CElementTmpl> it = mapElements.values().iterator();
	while (it.hasNext()) {
	    final CElementTmpl t = it.next();
	    t.print(prefix);
	}

    }

    public void put(final TTConnection connection, final Integer id,
	    final CElementTmpl element) throws SQLException {
	element.refresh(connection);
	mapElements.put(id, element);

    }

    public void refresh(final TTConnection connection) throws SQLException {
	clear();
    }

}
