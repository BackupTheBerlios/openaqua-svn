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
public class CElementTmplList extends CListableObject{
	private Map<Integer, CElementTmpl> mapElements = new TreeMap<Integer, CElementTmpl>();


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
	public CElementTmpl get(Integer id) {
		return mapElements.get(id);
	}


	public void put(TTConnection connection, Integer id, CElementTmpl element) throws SQLException {
		element.refresh(connection);
		mapElements.put(id, element);
		
	}

	public void refresh(TTConnection connection) throws SQLException {
		clear();
	}
	
	
	public void print(final String prefix) {
		Iterator<CElementTmpl> it = mapElements.values().iterator();
		while(it.hasNext()) {
			it.next().print(prefix);
		}
		
	}

	
	public String getElementsValues(Set<Integer> values) {
		String result = "";
		Iterator<CElementTmpl> it = mapElements.values().iterator();
		while(it.hasNext()) {
			CElementTmpl element = it.next();
			if (values.contains(element.getSubType().getId())) {
				result += element.getValue() + sep();
			}
		}
		return result;
	}
	
	

}
