/**
 * 
 */
package de.tmobile.cabu;

import java.sql.SQLException;

/**
 * @author behrenan
 *
 */
public class TTGenerator extends Thread{
	
	private int done = 0;
	private int maxContracts = Configuration.getInstance().getMaxContracts();
	TTConnection connection = null;
	
	
	
	/**
	 * Constructor
	 * @throws ClassNotFoundException 
	 */
	public TTGenerator(String threadName) throws ClassNotFoundException {
		super( threadName); 
		connection = new TTConnection("com.timesten.jdbc.TimesTenDriver", "jdbc:timesten:direct:RunData_tt51");

	}

	
	/**
	 * Init this thread
	 *
	 */
	public void Init(){
		try {
			connection.Connect();
		} catch (SQLException e) {
			connection.reportSQLException(e);
			throw new RuntimeException("Error while Database Connect");
		}
		 
	}




	private void executeRead() {
		long start = System.nanoTime();
		connection.executeRead(done++);
		long diff = System.nanoTime();
		Stats.getInstance().addReadResults(1, diff - start);
		yield();
	}

	private void executeWrite() {
		
		done++;
	}

	
	/**
	 * The thread execution method
	 * runs endless
	 */
	public void run () {
		try {
			while (done < maxContracts) {
				executeRead();
			}
		} catch (Exception e) {
			System.out.println( "Murks");
			e.printStackTrace();
			return;
		}
		connection.Disconnect();
		
	}
}
