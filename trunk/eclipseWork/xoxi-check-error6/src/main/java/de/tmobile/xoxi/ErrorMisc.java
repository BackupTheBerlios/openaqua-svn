/**
 * 
 */
package de.tmobile.xoxi;

import java.io.IOException;
import java.util.Collection;
import java.util.Iterator;
import java.util.LinkedList;

/**
 * @author behrenan
 * 
 */
public class ErrorMisc {
	private static ErrorMisc INSTANCE = new ErrorMisc();

	private Collection listOther = new LinkedList();

	public static ErrorMisc getInstance() {
		return INSTANCE;
	}

	public void add(LogFileLine line) {
		listOther.add(line);

	}

	public int countOtherErrors() {
		return listOther.size();
	}

	public void print() throws IOException {
		if (countOtherErrors() <= 0) return;
		Logger log = Logger.getRootLogger();
		log.smallHeader();
		log.out("Found " + countOtherErrors() + " Unknown Error Type");
		Iterator it = listOther.iterator();
		for (int max = 0; (max < 3) && it.hasNext(); max++) {
			LogFileLine l = (LogFileLine) it.next();
			l.print(3);
		}
		log.empty();
	}
}
