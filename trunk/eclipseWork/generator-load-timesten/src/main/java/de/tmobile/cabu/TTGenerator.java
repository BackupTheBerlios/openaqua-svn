/**
 * 
 */
package de.tmobile.cabu;

import java.sql.SQLException;
import java.util.Random;

/**
 * @author behrenan
 *
 */
public class TTGenerator extends Thread{

	private int done = 0;
	private int maxContracts = Configuration.getInstance().getMaxContracts();
	TTConnection connection = null;
    Random random = new Random();



	/**
	 * Constructor
	 * @throws ClassNotFoundException 
	 */
	public TTGenerator(String threadName) throws ClassNotFoundException {
		super( threadName); 
		connection = new TTConnection();

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
		//System.out.println("Execution in Thread: "+ getName());
		int contractID = 1 + Math.abs(random.nextInt()) % 49;
		long start = System.nanoTime();
		connection.executeRead(contractID);
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
		int loop = 0;
		try {
			for (int i = 0; i < Configuration.getInstance().getReqLoops(); i++){
				done = 0;
				while (done < maxContracts) {
					executeRead();
					loop++;
					done++;
				}

			}
		} catch (Exception e) {
			System.out.println( "Murks");
			e.printStackTrace();
			return;
		}
		connection.Disconnect();
		System.out.println("Execution in Thread: "+ getName() + " with "+loop+" loops");

	}
}
