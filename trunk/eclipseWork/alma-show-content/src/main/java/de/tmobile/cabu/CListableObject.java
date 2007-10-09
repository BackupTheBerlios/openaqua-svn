/**
 * 
 */
package de.tmobile.cabu;

/**
 * @author behrenan
 *
 */
public abstract class CListableObject {
	
	public String spaces(Integer spaces) {
		String result = "";
		for (Integer i = 0;i < spaces;i++) {
			result = result + sep();
		}
		return result;
	}

	public String sep() {
		return "\t";
	}
	
	abstract public void list(String type, Integer spaces);

}
