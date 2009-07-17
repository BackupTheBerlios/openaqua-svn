/**
 * 
 */
package de.tmobile.cabu;


import java.text.NumberFormat;


/**
 * @author behrenan
 * 
 */
public class PerfMonitor {
	private long counter;
	private long begin;
	private long endPrep;
	private long endQuery;
	private long endResult;

	public PerfMonitor() {
		super();
		begin();
	}

	public void begin() {
		counter = 0;
		endPrep = endQuery = endResult = 0;
		begin = System.nanoTime();

	}

	public long counter() {
		return counter;
	}

	public void endPrep() {
		endPrep = System.nanoTime();
	}

	public void endQuery() {
		endQuery = System.nanoTime();
	}

	public void endResult() {
		endResult = System.nanoTime();
	}

	private long getAll() {
		return endResult - begin;
	}


	final protected long getMicros(final long nanosecs) {
		return java.util.concurrent.TimeUnit.NANOSECONDS.toMicros(nanosecs);
	}

	final protected long getMillis(final long nanosecs) {
		return java.util.concurrent.TimeUnit.NANOSECONDS.toMillis(nanosecs);
	}

	final protected long getPrep() {
		final long result = endPrep - begin;
		if (result <= 0) { return 1; }
		return result;
	}

	final protected long getQuery() {
		final long result = endQuery - endPrep;
		if (result <= 0) { return 1; }
		return result;
	}

	final protected long getResult() {
		final long result = endResult - endQuery;
		if (result <= 0) { return 1; }
		return result;
	}

	public String getStatisticPrintString(final String classname) {
		long time = getMillis(getAll());
		if (time <= 0) {
			time = 1;
		}

		String result = String.format("%-45s", classname);
		result += String.format("Records=%8s\t", NumberFormat.getIntegerInstance().format(counter));
		result += String.format("Time=%6sms\t", NumberFormat.getIntegerInstance().format(time));
		if (counter == 0) {
			result += String.format("pRec=%5sµ\t", NumberFormat.getIntegerInstance().format(0));
		} else {
			result += String.format("pRec=%5sµ\t", NumberFormat.getIntegerInstance().format(getMicros(getAll()) / counter));
		}
		//result += String.format(" Prep=%5s", NumberFormat.getIntegerInstance().format(getMicros(getPrep())));
		//result += String.format(" Query=%8s", NumberFormat.getIntegerInstance().format(getMicros(getQuery())));
		//result += String.format(" Load=%8s", NumberFormat.getIntegerInstance().format(getMicros(getResult())));
		return result;

	}

	public void increase() {
		counter++;
	}


	public void setCounter(final long counter) {
		this.counter = counter;
	}
}
