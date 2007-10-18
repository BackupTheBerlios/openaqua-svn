/**
 * 
 */
package de.tmobile.xoxi;

import java.util.Collection;
import java.util.Iterator;
import java.util.regex.*;

/**
 * @author behrenan
 *
 */
public class Error6Parser {
///	static Pattern refTime = Pattern.compile(".*AttrGroupRefTime(V/T/R=2/10/0)={refTimestamp=[0-9]?,}");
	static Pattern refTime = Pattern.compile(".*AttrGroupRefTime");
	public void parse(Iterator it, Collection target) {
		while(it.hasNext()) {
			Object o = it.next();
			if (o instanceof LogFileLine) {
				LogFileLine line = (LogFileLine) o;
				parseLine(line, target);
				
			}
		}
	}
	
	private void parseLine(LogFileLine line, Collection target) {
		//if (! line.getMessage().startsWith("(ASYNC) has no pricelist and no counter with fixprice or 100% discoun")) return;
		//Logger.getRootLogger().error(line.getMessage().indexOf());
		//Error6 err = new Error6();
		
	}
}
