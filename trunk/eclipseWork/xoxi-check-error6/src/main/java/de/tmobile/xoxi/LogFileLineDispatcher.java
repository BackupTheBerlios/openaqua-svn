/**
 * 
 */
package de.tmobile.xoxi;

import java.util.Iterator;

/**
 * @author behrenan
 *
 */
public class LogFileLineDispatcher {
	
	public static void parse(Iterator it) {
		while(it.hasNext()) {
			Object o = it.next();
			if (o instanceof LogFileLine) {
				LogFileLine line = (LogFileLine) o;
				parseLine(line);
				
			}
		}
	}

	private static  void parseLine(LogFileLine line) {
		if (isEmty(line)) return;
		else if (isStatistic(line)) Statistic.getInstance().add(line);
		else if (isError6(line)) Error6.getInstance().add(line);
		return;
			
	}
	
	private static boolean isEmty(LogFileLine line) {
		final String msg = line.getMessage();
		if (msg == null || msg.length()<1) {
			return true;
		} else {
			return false;
		}
	}
	
	private static boolean isStatistic(LogFileLine line) {
		final String msg = line.getMessage();
		if (msg != null && msg.startsWith("statistics for ")) {
			return true;
		} else {
			return false;
		}
	}
	
	private static boolean isError6(LogFileLine line) {
		final String msg = line.getMessage();
		if (msg != null && msg.startsWith("statistics for ")) {
			return true;
		} else {
			return false;
		}
	}
}
