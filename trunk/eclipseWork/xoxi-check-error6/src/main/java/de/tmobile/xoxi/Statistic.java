/**
 * 
 */
package de.tmobile.xoxi;

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
			lines ++;
		} catch (NumberFormatException e) {
			Logger.getRootLogger().error("Could not parse line "+line);
		}

	}
	
	
	
	public long getAverageTime() {
		if (time == 0) return 0;
		else return time/amount;
	}

	
	
	public int getReadStatLines() {
		return lines;
	}
	
	public void print() {
		Logger log = Logger.getRootLogger();
		log.out("-------------------------------------------------------------");
		log.out("Static Average: "+Statistic.getInstance().getAverageTime());
		log.out("Static Amount of read Lines: "+Statistic.getInstance().getReadStatLines());
		log.out("");
	}
}
