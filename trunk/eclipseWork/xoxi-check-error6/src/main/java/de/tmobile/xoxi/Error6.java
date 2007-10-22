/**
 * 
 */
package de.tmobile.xoxi;

import java.util.Collection;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Map;
import java.util.TreeMap;


/**
 * @author behrenan
 *
 */
public class Error6 {
	private static Error6 INSTANCE = new Error6();
	private Map mapByVasCodeGroup 	 	= new TreeMap();
	private Map mapByVasCodeService 	= new TreeMap();
	private Collection listOther		= new LinkedList();
	
	public static Error6 getInstance() {
		return INSTANCE;
	}

	private Error6() {
		super();
	}
	
	
	public void add(LogFileLine line) {
		Error6Entry entry = new Error6Entry(line);
		if (entry.getVasCodeGroup().length() > 0) {
			Collection col = (Collection)mapByVasCodeGroup.get(entry.getVasCodeGroup());
			if (col == null) {
				col = new LinkedList();
				mapByVasCodeGroup.put(entry.getVasCodeGroup(), col);
			}
			col.add(entry);
			
		} else if (entry.getVasCodeService().length() > 0) {
			Collection col = (Collection)mapByVasCodeService.get(entry.getVasCodeService());
			if (col == null) {
				col = new LinkedList();
				mapByVasCodeService.put(entry.getVasCodeService(), col);
			}
			col.add(entry);
			
		} else {
			listOther.add(entry);
		
			
		}
		
	}
	
	public int countVasCodeGroupErrors() {
		Iterator it = mapByVasCodeGroup.values().iterator();
		int result = 0;
		while(it.hasNext()) {
			Collection col = (Collection)it.next();
			result += col.size();
		}
		return result;
	}
	
	public int countVasCodeServiceErrors() {
		Iterator it = mapByVasCodeService.values().iterator();
		int result = 0;
		while(it.hasNext()) {
			Collection col = (Collection)it.next();
			result += col.size();
		}
		return result;
	}

	public int otherErrors() {
		return listOther.size();
	}
	
	public void print() {
		Logger log = Logger.getRootLogger();
		log.out("-------------------------------------------------------------");
		log.out("Found "+countVasCodeGroupErrors()+" Errors with VasCodeGroup:");
		log.out("");
		
		log.out("-------------------------------------------------------------");
		log.out("Found "+countVasCodeServiceErrors()+" Errors with VasCodeService:");
		log.out("");

		log.out("-------------------------------------------------------------");
		log.out("Found "+countVasCodeServiceErrors()+" Errors with other Errors:");
		log.out("");
	}
}
