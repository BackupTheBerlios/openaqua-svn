/**
 * 
 */
package de.tmobile.cabu;


import java.io.FileWriter;
import java.io.IOException;


/**
 * @author behrenan
 * 
 */
public class CAlmaFileWriterThread implements Runnable {
	final BaseList list;
	final String name;

	public CAlmaFileWriterThread(final String name, final BaseList list) {
		super();
		this.list = list;
		this.name = name;
	}


	public void run() {
		FileWriter fw = null;
		final PerfMonitor perfMonitor = new PerfMonitor();
		perfMonitor.begin();
		try {
			//create a new file
			fw = new FileWriter(name);
			perfMonitor.endPrep();

			//write file header
			if (list.getPrintDescription() != null) {
				fw.write(list.getPrintDescription());
			}
			if (list.getPrintHeader("") != null) {
				fw.write(list.getPrintHeader(""));
			}
			perfMonitor.endQuery();


			//write file content
			for (final BaseType type : list.values()) {
				fw.write(type.getPrintString("") + "\n");
				perfMonitor.increase();
			}
		} catch (final IOException e) {
			System.err.println("Konnte Datei nicht erstellen");
		} finally {
			if (fw != null) {
				try {
					fw.close();
				} catch (final IOException e) {}
			}
		}
		perfMonitor.endResult();
		CLogger.getRootLogger().info(perfMonitor.getStatisticPrintString(name));

	}
}
