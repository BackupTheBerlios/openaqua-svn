/**
 * 
 */
package de.tmobile.cabu;

import java.util.Iterator;



/**
 * @author behrenan
 * 
 */
public class LogFileLineDispatcher {

	private static boolean isChcNoPriceListMmsg(final LogFileLine line) {
		final String msg = line.getMessage();
		if (msg != null && msg.equals("(ASYNC) Error-Response: code = 6, text = 'has no pricelist and no counter with fixprice or 100% discount'")) {
			return true;
		} else {
			return false;
		}
	}


	private static boolean isChcOneOrMoreCounterLocked(final LogFileLine line) {
		final String msg = line.getMessage();
		if (msg != null && msg.equals("(ASYNC) Error-Response: code = 6, text = '1 or more counter locked.'")) {
			return true;
		} else {
			return false;
		}
	}


	private static boolean isComingRequest(final LogFileLine line) {
		final String msg = line.getMessage();
		if (msg != null && msg.startsWith("coming requests are served by ")) {
			return true;
		} else {
			return false;
		}
	}


	private static boolean isEmty(final LogFileLine line) {
		final String msg = line.getMessage();
		if (msg == null || msg.length() < 1) {
			return true;
		} else {
			return false;
		}
	}


	private static boolean isError6(final LogFileLine line) {
		final String msg = line.getMessage();
		if (msg != null && msg.startsWith("(ASYNC) has no pricelist and no counter with fixprice or 100% discount / rexRequest(T =49188)=")) {
			return true;
		} else {
			return false;
		}
	}


	private static boolean isErrorNoAlma(final LogFileLine line) {
		final String msg = line.getMessage();
		if (msg != null && msg.startsWith("(ASYNC) Request has no counterValues (no Alma?) but tries to use counterAppliances  / rexRequest(T =49188)={seqNr=")) {
			return true;
		} else {
			return false;
		}
	}


	private static boolean isRequestCompleted(final LogFileLine line) {
		final String msg = line.getMessage();
		if (msg != null && msg.startsWith("request completed in ")) {
			return true;
		} else {
			return false;
		}
	}


	private static boolean isRequestTimedOut(final LogFileLine line) {
		final String msg = line.getMessage();
		if (msg != null && msg.startsWith("request timed out")) {
			return true;
		} else {
			return false;
		}
	}


	private static boolean isStatistic(final LogFileLine line) {
		final String msg = line.getMessage();
		if (msg != null && msg.startsWith("statistics for ")) {
			return true;
		} else {
			return false;
		}
	}


	public static void parse(final Iterator it) {
		while (it.hasNext()) {
			final Object o = it.next();
			if (o instanceof LogFileLine) {
				parseLine((LogFileLine) o);

			}
		}
	}


	private static void parseLine(final LogFileLine line) {
		if (isEmty(line)) {
			return;
		} else if (isStatistic(line)) {
			Statistic.getInstance().add(line);
			return;
		} else if (isError6(line)) {
			Error6.getInstance().add(line);
			return;
		} else if (isErrorNoAlma(line)) {
			ErrorNoAlma.getInstance().add(line);
			return;
		} else if (isComingRequest(line)) {
			return;
		} else if (isRequestCompleted(line)) {
			return;
		} else if (isRequestTimedOut(line)) {
			return;
		} else if (isChcNoPriceListMmsg(line)) {
			ErrorChc.getInstance().increaseErrNoPricelist();
			return;
		} else if (isChcOneOrMoreCounterLocked(line)) {
			ErrorChc.getInstance().increaseErrCounterLocked();
			return;
		} else {
			ErrorMisc.getInstance().add(line);
			return;
		}
	}

}
