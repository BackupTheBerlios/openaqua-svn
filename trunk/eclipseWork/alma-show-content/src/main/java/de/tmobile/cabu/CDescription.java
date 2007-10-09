/**
 * 
 */
package de.tmobile.cabu;

import java.util.HashMap;
import java.util.Map;

/**
 * @author behrenan
 *
 */
public class CDescription {
	private Map<Integer, String> description;
	
	public CDescription () {
		description = new HashMap<Integer, String>();
	}
	
	public void add(Integer id, String value) {
		description.put(id, value);
	}
	
	public void clear() {
		description.clear();
	}
	
	public String get(Integer id) {
		String result = "<unknown>";
		if (description.containsKey(id)) {
			result = description.get(id);
		} 
		return result;
	}
}
