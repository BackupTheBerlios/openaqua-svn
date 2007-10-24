/**
 * 
 */

package de.tmobile.cabu;

import java.io.IOException;
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
	private static Error6	INSTANCE	= new Error6();


	public static Error6 getInstance() {
		return INSTANCE;
	}

	private final Map	     mapByVasCodeGroup	 = new TreeMap();
	private final Map	     mapByVasCodeService	= new TreeMap();

	private final Collection	listOther	     = new LinkedList();


	private Error6() {
		super();
	}


	public void add(final LogFileLine line) {
		final ErrorEntry entry = new ErrorEntry(line);
		if (entry.getVasCodeGroup().length() > 0) {
			Collection col = (Collection) mapByVasCodeGroup.get(entry.getVasCodeGroup());
			if (col == null) {
				col = new LinkedList();
				mapByVasCodeGroup.put(entry.getVasCodeGroup(), col);
			}
			col.add(entry);

		} else if (entry.getVasCodeService().length() > 0) {
			Collection col = (Collection) mapByVasCodeService.get(entry.getVasCodeService());
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


	public int countVasCodeErrors(final Map map) {
		final Iterator it = map.values().iterator();
		int result = 0;
		while (it.hasNext()) {
			final Collection col = (Collection) it.next();
			result += col.size();
		}
		return result;
	}


	public int countVasCodeGroupErrors() {
		return countVasCodeErrors(mapByVasCodeGroup);
	}


	public int countVasCodeServiceErrors() {
		return countVasCodeErrors(mapByVasCodeService);
	}


	public int otherErrors() {
		return listOther.size();
	}


	public void print() throws IOException {
		final Logger log = Logger.getRootLogger();
		if (countVasCodeGroupErrors() > 0) {
			log.smallHeader();
			log.out("Found " + countVasCodeGroupErrors() + " Errors with VasCodeGroup:");
			printVasCodeErrors(mapByVasCodeGroup);
			log.empty();
		}

		if (countVasCodeServiceErrors() > 0) {
			log.smallHeader();
			log.out("Found " + countVasCodeServiceErrors() + " Errors with VasCodeService:");
			printVasCodeErrors(mapByVasCodeService);
			log.empty();
		}

		if (countOtherErrors() > 0) {
			log.smallHeader();
			log.out("Found " + countOtherErrors() + " Errors with other Errors:");
			log.empty();
		}
	}


	public void printVasCodeErrors(final Map map) throws IOException {
		if (map.size() <= 0) { return; }
		int max = countVasCodeErrors(map) / map.size() + 1;
		if (max > 8) {
			max = 8;
		}

		final Iterator it = map.keySet().iterator();
		while (it.hasNext()) {
			final String key = (String) it.next();
			final Collection col = (Collection) map.get(key);
			if (max > col.size()) {
				Logger.getRootLogger().out("VasCode " + key + ": found " + col.size() + " error(s)");
			} else {
				Logger.getRootLogger().out("VasCode " + key + ": found " + col.size() + " error(s), show " + max + " only");
			}
			final Iterator cit = col.iterator();
			for (int cur = 0; cit.hasNext(); cur++) {
				if (!Configuration.getInstance().isShowAll()) {
					if (cur >= max) {
						break;
					}
				}
				final ErrorEntry e = (ErrorEntry) cit.next();
				e.print(3);
			}
			Logger.getRootLogger().out("   ");
		}
	}
}
