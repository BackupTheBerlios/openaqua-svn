/**
 * 
 */
package de.tmobile.cabu;

import java.sql.SQLException;
import java.util.Iterator;
import java.util.Map;
import java.util.TreeMap;
import java.util.Map.Entry;

/**
 * @author behrenan
 *
 */
public class CIdentificationList extends CListableListObject  {
	private Map<Integer, CIdentification> mapElements = new TreeMap<Integer, CIdentification>();
	
	private static CIdentificationList  INSTANCE = new CIdentificationList ();
	public static CIdentificationList getInstances() {
		return INSTANCE;		
	}
	
	public CIdentificationList() {
		super();
	}
	

	@Override
	public void refresh(TTConnection connection) throws SQLException {
		clear();
	}
	
	@Override
	public void print(String prefix) {
		Iterator<Entry<Integer, CIdentification>> it = mapElements.entrySet().iterator();
		while(it.hasNext()) {
			it.next().getValue().print(prefix);
		}
	}

	@Override
	public void clear() {
		mapElements.clear();
	}

}
