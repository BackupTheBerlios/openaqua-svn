/**
 *
 */
package de.tmobile.cabu.loadtest;

import java.sql.SQLException;
import java.util.Random;

/**
 * @author behrenan
 *
 */
public class TTGenerator extends Thread{

	private int done = 0;
	private int maxContracts = Configuration.getInstance().getMaxContracts();
	private TTConnection connection = null;
    private Random random = new Random();



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
		int contractID = 1 + Math.abs(random.nextInt()) % Configuration.getInstance().getMaxContracts();
		connection.executeRead(contractID);
		Stats.getInstance().addReadResults(1);
		yield();
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
					//executeWrite();
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
	}
}
