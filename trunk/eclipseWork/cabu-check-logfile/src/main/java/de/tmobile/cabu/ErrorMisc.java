/**
 * 
 */
package de.tmobile.cabu;

import java.util.Collection;
import java.util.Iterator;
import java.util.LinkedList;



/**
 * @author behrenan
 * 
 */
public class ErrorMisc {
	private static ErrorMisc	INSTANCE	= new ErrorMisc();


	public static ErrorMisc getInstance() {
		return INSTANCE;
	}

	private final Collection	listOther	= new LinkedList();


	public void add(final LogFileLine line) {
		listOther.add(line);

	}


	public int countOtherErrors() {
		return listOther.size();
	}


	public void print() {
		if (countOtherErrors() <= 0) { return; }
		final Logger log = Logger.getRootLogger();
		log.smallHeader();
		log.out("Found " + countOtherErrors() + " Unknown Error Type");
		final Iterator it = listOther.iterator();
		for (int max = 0; max < 3 && it.hasNext(); max++) {
			final LogFileLine l = (LogFileLine) it.next();
			l.print(3);
		}
		log.empty();
	}
}
