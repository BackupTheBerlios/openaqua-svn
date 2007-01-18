/**
 * 
 */
package de.tmobile.cabu;

import java.sql.Connection;
import java.sql.DataTruncation;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.SQLWarning;
import java.sql.Statement;

/**
 * @author behrenan
 *
 */
public class TTConnection {
	boolean hasReceivedSignal = false;
	private boolean isDriverLoaded;
	private String driver;
	private String url;
	boolean shouldWait = false;
	Object stopMonitor = new Object();
	private boolean isConnected = false;
	Connection connection = null;



	public void loadDriver() throws ClassNotFoundException
	{
		if (!isDriverLoaded) {
			System.out.println("loadDriver(): " + driver);
			// Load TimesTen JDBC driver using Class.forName()
			
			Class.forName(driver);
			isDriverLoaded = true;
		}
	}
	
	public static void reportSQLException(SQLException ex)
	{
		int errCount = 0;

		while (ex != null) {
			System.err.println ("\n\t----- SQL Error -----");

			System.err.println ("\tError Message: " + ex.getMessage ());
			if (errCount == 0) {
				ex.printStackTrace ();
			}

			System.err.println ("\tSQL State: " + ex.getSQLState ());
			System.err.println ("\tNative Error Code: " + ex.getErrorCode ());
			System.err.println ("");

			ex = ex.getNextException ();
			errCount ++;
		}
	}

	/**
	 * prints all attributes of a SQLWarning object to
	 * System.err and all chained warnings
	 */
	public static void reportSQLWarning(SQLWarning wn)
	{
		int warnCount = 0;

		while (wn != null) {
			System.err.println ("\n\t----- SQL Warning -----");

			// Is this a regular SQLWarning object or a DataTruncation object?
			if (wn instanceof DataTruncation) {
				DataTruncation trn = (DataTruncation) wn;
				System.err.println ("\tData Truncation Warning: " + trn.getMessage ());
				if (warnCount == 0) {
					trn.printStackTrace ();
				}

				System.err.println ("\tSQL State: " + trn.getSQLState ());
				System.err.println ("\tNative Error Code: " + trn.getErrorCode ());

				System.err.println ("\n\tgetIndex (): " + trn.getIndex ());
				System.err.println ("\tgetParameter (): " + trn.getParameter ());
				System.err.println ("\tgetRead (): " + trn.getRead ());
				System.err.println ("\tgetDataSize (): " + trn.getDataSize ());
				System.err.println ("\tgetTransferSize (): " + trn.getTransferSize ());
			} else {
				System.err.println ("\tWarning Message: " + wn.getMessage ());
				if (warnCount == 0) {
					wn.printStackTrace ();
				}

				System.err.println ("\tSQL State: " + wn.getSQLState ());
				System.err.println ("\tNative Error Code: " + wn.getErrorCode ());
			}

			System.err.println ("");

			wn = wn.getNextWarning ();
			warnCount++;
		}
	}

	
	
	public void Connect() 
	{
		System.out.println("Connect");
	
		try {
			System.out.println("Open a connection.");
			isConnected = true;
			connection = DriverManager.getConnection(url);
			reportSQLWarning(connection.getWarnings());
			connection.setAutoCommit (false);

		} catch (SQLException ex) {
			reportSQLException(ex);
		}
	}

	
	
	
	public void Disconnect()
	{
		try {
			if (connection != null && connection.isClosed() == false) {
				// Close the connection
				System.out.println("Close the connection.");
				connection.close();
			}
			isConnected = false;
		}  catch (SQLException ex) {
			reportSQLException(ex);
		}
	}
	

	public TTConnection(String driver, String url) throws ClassNotFoundException
	{
		this.isDriverLoaded = false;
		this.driver = driver;
		this.url = url;
		loadDriver();
	}

	public void BeginTransaction() {
		if (isConnected == false) return;
	}

	public void CommitTransaction() {
		if (isConnected == false) return;
		try {
			if (connection != null && connection.isClosed() == false) {
				connection.commit();
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	public void RollbackTransaction() {
		if (isConnected == false) return;
		try {
			if (connection != null && connection.isClosed() == false) {
				connection.rollback();
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}
		
	}
	
	public void CreateTableStructure() throws SQLException {
		if (isConnected == false) return;
		
		BeginTransaction();
		Statement stmt = connection.createStatement();

		//setup job list
		stmt.addBatch ("CREATE TABLE Contract (C1 INTEGER)");
		stmt.addBatch ("INSERT INTO Contract VALUES (1)");
		stmt.addBatch ("INSERT INTO Contract VALUES (2)");
		stmt.addBatch ("INSERT INTO Contract VALUES (3)");
		stmt.addBatch ("INSERT INTO Contract VALUES (4)");
		stmt.addBatch ("INSERT INTO Contract VALUES (5)");
		
		
		//execute and commit
		stmt.executeBatch();
		CommitTransaction();
	}
	

}
