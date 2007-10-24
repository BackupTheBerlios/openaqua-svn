/**
 * 
 */
package de.tmobile.cabu;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;



/**
 * @author behrenan
 * 
 */
/**
 * @author behrenan
 * 
 */
public class LogFile {
	private final File	     logfile;
	private final Collection	lines;
	Logger	                 logger	= Logger.getRootLogger();


	/***************************************************************************
	 * 
	 * @return
	 */
	public LogFile(final String filename) throws FileNotFoundException {
		super();
		logfile = new File(filename);
		lines = new ArrayList();
	}


	public Iterator iterator() {
		return lines.iterator();
	}


	/***************************************************************************
	 * 
	 * @return
	 * @throws IOException
	 */
	public int print() throws IOException {
		final Iterator it = lines.iterator();
		while (it.hasNext()) {
			final LogFileLine line = (LogFileLine) it.next();
			logger.out(line.getTime() + "\t" + line.getSystem() + "\t" + line.getProcess());
		}
		return 0;
	}


	/***************************************************************************
	 * 
	 * @return
	 */
	public int read() throws FileNotFoundException {
		final FileReader reader = new FileReader(logfile);
		final BufferedReader breader = new BufferedReader(reader);

		try {
			for (String line; (line = breader.readLine()) != null;) {
				final String[] parts = line.split(";");
				final LogFileLine entry = new LogFileLine();
				entry.setTime(parts[0]);
				entry.setSystem(parts[1]);
				// entry.setTime(parts[2]);
				entry.setProcess(parts[3]);
				entry.setId(Integer.valueOf(parts[4]).intValue());
				entry.setType(parts[5]);
				entry.setNumber(Integer.valueOf(parts[6]).intValue());
				entry.setMessage(parts[7]);
				lines.add(entry);
			}
		} catch (final Exception e) {
			e.printStackTrace();
		}
		Statistic.getInstance().setReadLines(lines.size());
		return 0;
	}
}
