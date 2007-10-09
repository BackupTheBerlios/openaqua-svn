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
public class CTemplate {
	Integer rootId;
	Map<Integer, CAttribute> attributes;
	
	public CTemplate(Integer rootId) {
		super();
		attributes = new HashMap<Integer, CAttribute>();
		this.rootId = rootId;
	}

	public void clearAttributes() {
		attributes.clear();
	}
	
	public void addAttribute(CAttribute attribute) {
		this.attributes.put(attribute.getElementId(), attribute);
	}
}
