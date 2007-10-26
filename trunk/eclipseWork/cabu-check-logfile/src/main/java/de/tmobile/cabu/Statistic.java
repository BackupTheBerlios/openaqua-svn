/**
 * 
 */
package de.tmobile.cabu;

import java.io.File;
import java.net.InetAddress;
import java.net.UnknownHostException;



/**
 * @author behrenan
 * 
 */
public class Statistic {
	private static Statistic	INSTANCE	= new Statistic();


	public static Statistic getInstance() {
		return INSTANCE;
	}

	private long	amount;
	private long	time;

	private int	 lines;


	private Statistic() {
		super();
		amount = 0;
		time = 0;
		lines = 0;
	}


	public void add(final LogFileLine entry) {
		final String line = entry.getMessage();
		if (line == null) { return; }
		if (!line.startsWith("statistics for ")) { return; }

		final String[] parts = line.split(" ");
		try {
			// add amount of records
			final int c = Integer.valueOf(parts[2]).intValue();
			final int t = Integer.valueOf(parts[parts.length - 2]).intValue();
			amount += c;
			time += t * c;
		} catch (final NumberFormatException e) {
			Logger.getRootLogger().error("Could not parse line " + line);
		}

	}


	public long getAverageTime() {
		if (amount == 0) { return 0; }
		return time / amount;

	}


	public int getReadStatLines() {
		return lines;
	}


	public long getRequestsDay() {
		return amount;
	}


	public long getRequestsMinute() {
		return amount / 24 / 60;
	}


	public void print() {
		String hostname = "<unknown>";
		String fqhostname = "<unknown>";
		String ip = "<unknown>";
		try {
			hostname = InetAddress.getLocalHost().getHostName();
			fqhostname = InetAddress.getLocalHost().getCanonicalHostName();
			ip = InetAddress.getLocalHost().getHostAddress();

		} catch (final UnknownHostException e) {}

		final Logger log = Logger.getRootLogger();
		log.out("-------------------------------------------------------------");
		switch (Configuration.getInstance().getLogFileType()) {
		case 1:
			log.out("Application       : CHC");
			break;
		case 2:
			log.out("Application       : XOXI");
			break;
		default:
			log.out("Application       : Unknown, Type ID " + Configuration.getInstance().getLogFileType());
		}
		log.out("Logfile           : " + new File(Configuration.getInstance().getLogFile()).getName());
		log.empty();
		log.out("Statistic         : " + getRequestsDay() + " Requests/Day");
		log.out("Statistic Average : " + getAverageTime() + " Microsec/Request");
		log.out("Statistic Average : " + getRequestsMinute() + " Requests/Min");
		log.out("Checked           : " + getReadStatLines() + " lines of Logfile");
		log.empty();
		log.out("hostname          : " + hostname);
		log.out("FQ hostname       : " + fqhostname);
		log.out("IP Address        : " + ip);
		log.empty();
		log.empty();
		log.empty();
		log.empty();
	}


	public void setReadLines(final int lines) {
		this.lines = lines;
	}
}
