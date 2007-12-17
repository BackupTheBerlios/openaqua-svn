/**
 * 
 */
package de.tmobile.cabu;


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

	public String getConsumedTime() {
		String result = "\t";
		result += "All=" + getMicros(getAll()) + "\t";
		result += "Preparation=" + getMicros(getPrep()) + "\t";
		result += "Query=" + getMicros(getQuery()) + "\t";
		result += "Result=" + getMicros(getResult()) + "\t";
		result += "Amount=" + counter + "\t";
		result += "µ/Rec=" + getAll() / counter;
		return result;
	}

	private long getMicros(final long nanosecs) {
		return java.util.concurrent.TimeUnit.NANOSECONDS.toMicros(nanosecs);
	}

	private long getPrep() {
		return endPrep - begin;
	}

	private long getQuery() {
		return endQuery - endPrep;
	}

	private long getResult() {
		return endResult - endQuery;
	}

	public void increase() {
		counter++;
	}


	/*
	public String ouput() {
		final long mikRange = nanosecs();
		String head = "Performance:\t";
		final long myCount = counter;
		if (myCount <= 0) { return head + mikRange / 10 + "µ\t" + "0 Rec/ms "; }

		// time pro rec
		head += mikRange / myCount + "µ/Rec";

		//rec pro time
		//handle less than 1 ms
		if (mikRange < 1000) { return head + "\t" + counter + " Rec/ms"; }

		//handle more than 1 ms
		return head + "\t" + counter / (mikRange / 1000) + " Rec/ms";
	}
	*/


	public void setCounter(final long counter) {
		this.counter = counter;
	}
}
