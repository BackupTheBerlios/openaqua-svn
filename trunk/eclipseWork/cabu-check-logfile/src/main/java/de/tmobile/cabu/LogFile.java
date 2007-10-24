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
	private File logfile;
	private Collection lines;
	Logger logger = Logger.getRootLogger();

	
	/******************************************
	 * 
	 * @return
	 */
	public LogFile(final String filename) throws FileNotFoundException {
		super();
		logfile = new File(filename);
		lines = new ArrayList();
	}

	
	
	/******************************************
	 * 
	 * @return
	 */
	public int read() throws FileNotFoundException {
		FileReader reader = new FileReader(logfile);
		BufferedReader breader = new BufferedReader(reader);
		
		try {
			for ( String line; (line = breader.readLine()) != null; ) {
				String[] parts = line.split( ";");
				LogFileLine entry = new LogFileLine();
				entry.setTime(parts[0]);
				entry.setSystem(parts[1]);
				//entry.setTime(parts[2]);
				entry.setProcess(parts[3]);
				entry.setId(Integer.valueOf(parts[4]).intValue());
				entry.setType(parts[5]);
				entry.setNumber(Integer.valueOf(parts[6]).intValue());
				entry.setMessage(parts[7]);
				lines.add(entry);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		Statistic.getInstance().setReadLines(lines.size());
		return 0;
	}
	
	
	/******************************************
	 * 
	 * @return
	 * @throws IOException 
	 */
	public int print() throws IOException {
		Iterator it = lines.iterator();
		while(it.hasNext()) {
			LogFileLine line = (LogFileLine)it.next();
			logger.out(line.getTime()+"\t"+line.getSystem()+"\t"+line.getProcess());
		}
		return 0;
	}
	

	
	public Iterator iterator() {
		return lines.iterator();
	}
}
