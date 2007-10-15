/**
 * 
 */
package de.tmobile.cabu;



/**
 * @author behrenan
 *
 */
public abstract class CListableObject {
	public static String spaces(Integer spaces) {
		String result = "";
		for (Integer i = 0;i < spaces;i++) {
			result = result + sep();
		}
		return result;
	}

	public static String sep() {
		return "\t";
	}
	
	
	abstract public void print(final String prefix);
}
