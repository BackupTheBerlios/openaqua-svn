/**
 * 
 */
package de.tmobile.cabu;

import java.sql.SQLException;





/**
 * @author behrenan
 *
 */
public class Main {
	static TTConnection mainConnection = null;




	/**
	 * makes the measuring
	 * @throws ClassNotFoundException 
	 *
	 */
	private static void execution ()  {		

		//setup threads

	}


	/**
	 * @param args
	 * @throws InterruptedException 
	 * @throws ClassNotFoundException 
	 */
	public static void main(String[] args) throws InterruptedException {

		try {
			mainConnection = new TTConnection();
			mainConnection.Connect();
		} catch (ClassNotFoundException e1) {
			System.err.println("Java ClassNotFound: " + e1.getMessage());
			return;
		} catch (SQLException e) {
			System.err.println("SQLException: " + e.getMessage());
			e.printStackTrace();
		}

		execution();
		mainConnection.Disconnect();


	}

}
