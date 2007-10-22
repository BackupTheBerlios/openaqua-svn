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
		if (isEmty(line)) 					{ return;}
		else if (isStatistic(line)) 		{ Statistic.getInstance().add(line); return;}
		else if (isError6(line)) 			{ Error6.getInstance().add(line); return;}
		else if (isErrorNoAlma(line))		{ ErrorNoAlma.getInstance().add(line); return;}
		else if (isComingRequest(line))		{ return;}
		else if (isRequestCompleted(line))	{ return;}
		else if (isRequestTimedOut(line))	{ return;}
		else 								{ ErrorMisc.getInstance().add(line); return;}
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
		if (msg != null && msg.startsWith("(ASYNC) has no pricelist and no counter with fixprice or 100% discount / rexRequest(T =49188)=")) {
			return true;
		} else {
			return false;
		}
	}

	private static boolean isErrorNoAlma(LogFileLine line) {
		final String msg = line.getMessage();
		if (msg != null && msg.startsWith("(ASYNC) Request has no counterValues (no Alma?) but tries to use counterAppliances  / rexRequest(T =49188)={seqNr=")) {
			return true;
		} else {
			return false;
		}
	}
	
	private static boolean isComingRequest(LogFileLine line) {
		final String msg = line.getMessage();
		if (msg != null && msg.startsWith("coming requests are served by ")) {
			return true;
		} else {
			return false;
		}
	}

	private static boolean isRequestCompleted(LogFileLine line) {
		final String msg = line.getMessage();
		if (msg != null && msg.startsWith("request completed in ")) {
			return true;
		} else {
			return false;
		}
	}
	
	private static boolean isRequestTimedOut(LogFileLine line) {
		final String msg = line.getMessage();
		if (msg != null && msg.startsWith("request timed out")) {
			return true;
		} else {
			return false;
		}
	}
	
	
}
