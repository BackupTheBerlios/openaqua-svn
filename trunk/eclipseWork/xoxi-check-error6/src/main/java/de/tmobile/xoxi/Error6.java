/**
 * 
 */
package de.tmobile.xoxi;

import java.util.regex.*;


/**
 * @author behrenan
 *
 */
public class Error6 {
	private static Error6 INSTANCE = new Error6();
	public static Error6 getInstance() {
		return INSTANCE;
	}
	private Error6() {
		super();
	}
	
	
///	static Pattern refTime = Pattern.compile(".*AttrGroupRefTime(V/T/R=2/10/0)={refTimestamp=[0-9]?,}");
	static Pattern refTime = Pattern.compile(".*AttrGroupRefTime");
	public void add(LogFileLine line) {
	}
	
}
