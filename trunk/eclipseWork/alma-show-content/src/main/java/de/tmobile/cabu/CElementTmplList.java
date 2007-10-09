/**
 * 
 */
package de.tmobile.cabu;

import java.sql.SQLException;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.Map.Entry;

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

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.tmobile.cabu.IElementList#list()
	 */
	public void list(String type, Integer spaces) {
		Iterator<Entry<Integer, CElementTmpl>> it = mapElements.entrySet().iterator();
		while(it.hasNext()) {
			it.next().getValue().list(type, spaces);
		}

	}
	
	public void collectElementTmplSubTypes(Set<Integer> ids) {
		Iterator<Entry<Integer, CElementTmpl>> it = mapElements.entrySet().iterator();
		while(it.hasNext()) {
			it.next().getValue().collectElementTmplSubTypes(ids);
		}
	}

	public void put(TTConnection connection, Integer id, CElementTmpl element) throws SQLException {
		element.refresh(connection);
		mapElements.put(id, element);
		
	}

	public void refresh(TTConnection connection) throws SQLException {
		clear();
	}
	
	public String listHeader() {
		String line = "";
		line += "count"+sep();
		line += "type"+sep();
		line += "tmplId"+sep();
		line += "rootId" + sep();
		line += "parent" + sep();
		line += "objVers" + sep();
		//line += "validFrom" + sep();
		//line += "validTo" + sep();
		return line;
	}
	
	
	public void listFormated(Set<Integer> attributeTypes, String line) {
		Iterator<Entry<Integer, CElementTmpl>> it = mapElements.entrySet().iterator();
		int counter = 1;
		while(it.hasNext()) {
			line = ""+counter++ +sep();
			CElementTmpl element = it.next().getValue();
			line += element.getSubType().getDescription() + sep();
			line += element.getId() + sep();
			line += element.getRootId() + sep();
			line += element.getParentId() + sep();
			line += element.getObjVersion() + sep();
			//line += element.getValidFrom() + sep();
			//line += element.getValidTo() + sep();
			
			element.listFormated(attributeTypes, line);
			System.out.println(line);
		}
	}

}
