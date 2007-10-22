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
	private Map mapByVasCodeGroup = new TreeMap();
	private Map mapByVasCodeService = new TreeMap();
	private Collection listOther = new LinkedList();
	public static Error6 getInstance() {
		return INSTANCE;
	}

	private Error6() {
		super();
	}

	public void add(LogFileLine line) {
		ErrorEntry entry = new ErrorEntry(line);
		if (entry.getVasCodeGroup().length() > 0) {
			Collection col = (Collection) mapByVasCodeGroup.get(entry
					.getVasCodeGroup());
			if (col == null) {
				col = new LinkedList();
				mapByVasCodeGroup.put(entry.getVasCodeGroup(), col);
			}
			col.add(entry);

		} else if (entry.getVasCodeService().length() > 0) {
			Collection col = (Collection) mapByVasCodeService.get(entry
					.getVasCodeService());
			if (col == null) {
				col = new LinkedList();
				mapByVasCodeService.put(entry.getVasCodeService(), col);
			}
			col.add(entry);

		} else {
			listOther.add(entry);

		}

	}


	public int countOtherErrors() {
		return listOther.size();
	}

	public int countVasCodeErrors(Map map) {
		Iterator it = map.values().iterator();
		int result = 0;
		while (it.hasNext()) {
			Collection col = (Collection) it.next();
			result += col.size();
		}
		return result;
	}
	public int countVasCodeServiceErrors() {
		return countVasCodeErrors(mapByVasCodeService);
	}
	
	public int countVasCodeGroupErrors() {
		return countVasCodeErrors(mapByVasCodeGroup);
	}

	public int otherErrors() {
		return listOther.size();
	}

	public void printVasCodeErrors(Map map) {
		if (map.size() <= 0) return;
		int max = countVasCodeErrors(map)/map.size()+1;
		if (max > 5) max = 5;
		//Logger.getRootLogger().debug("MAX"+max);
		Iterator it = map.values().iterator();
		while (it.hasNext()) {
			Collection col = (Collection) it.next();
			Iterator cit = col.iterator();
			for(int cur = 0; (cur < max) && (cit.hasNext());cur++) {
				ErrorEntry e = (ErrorEntry) cit.next();
				e.print(3);
			}
			if (cit.hasNext()) Logger.getRootLogger().out("             ...");
			Logger.getRootLogger().out("   ");
		}
	}
	
	public void print() {
		Logger log = Logger.getRootLogger();
		if (countVasCodeGroupErrors() > 0) {
			log.out("-------------------------------------------------------------");
			log.out("Found " + countVasCodeGroupErrors()					+ " Errors with VasCodeGroup:");
			printVasCodeErrors(mapByVasCodeGroup);
			log.out("");
		}

		if (countVasCodeServiceErrors() > 0) {
			log.out("-------------------------------------------------------------");
			log.out("Found " + countVasCodeServiceErrors()				+ " Errors with VasCodeService:");
			printVasCodeErrors(mapByVasCodeService);
			log.out("");
		}

		if (countOtherErrors() > 0) {
			log.out("-------------------------------------------------------------");
			log.out("Found " + countOtherErrors() + " Errors with other Errors:");
			log.out("");
		}
	}
}
