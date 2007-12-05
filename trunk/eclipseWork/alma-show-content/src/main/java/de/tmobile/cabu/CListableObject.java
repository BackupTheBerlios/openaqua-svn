/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class CListableObject {
	public static String sep() {
		return "\t";
	}

	public static String spaces(final int spaces) {
		String result = "";
		for (int i = 0; i < spaces; i++) {
			result = result + sep();
		}
		return result;
	}

}
