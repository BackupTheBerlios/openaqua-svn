/**
 * 
 */
package de.tmobile.xoxi;

import java.io.IOException;

/**
 * @author behrenan
 *
 */
public class Statistic {
	private static Statistic INSTANCE = new Statistic ();
	private long amount;
	private long time;
	private int lines;
	
	private Statistic () {
		super();
		amount = 0;
		time = 0;
		lines = 0;
	}
	
	
	public static Statistic getInstance() {
		return INSTANCE;
	}
	
	
	
	public void add(final LogFileLine entry) {
		final String line = entry.getMessage(); 
		if (line == null) return; 
		if (!line.startsWith("statistics for ")) return;

		String[] parts = line.split( " " );
		try {
			//add amount of records
			int c = Integer.valueOf(parts[2]).intValue();
			int t = Integer.valueOf(parts[parts.length-2]).intValue();
			amount += c;
			time += (t*c);
		} catch (NumberFormatException e) {
			Logger.getRootLogger().error("Could not parse line "+line);
		}

	}
	
	public void setReadLines(final int lines) {
		this.lines = lines;
	}
	
	
	public long getRequestsMinute () {
		return amount/24/60;
	}
	public long getRequestsDay () {
		return amount;
	}
	
	public long getAverageTime() {
		if (amount == 0) return 0;
		return time/amount;
		
	}

	
	
	public int getReadStatLines() {
		return lines;
	}
	
	public void print() throws IOException {
		Logger log = Logger.getRootLogger();
		log.out("-------------------------------------------------------------");
		log.out("Statistic        : "+getRequestsDay()+ " Requests/Day");
		log.out("Statistic Average: "+getAverageTime() + " Microsec/Request");
		log.out("Statistic Average: "+getRequestsMinute()+ " Requests/Min");
		log.out("Checked "+getReadStatLines()+" lines Logfile");
		log.out("");
	}
}
