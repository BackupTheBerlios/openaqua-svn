/**
 *
 */
package de.tmobile.cabu;

import java.sql.Connection;
import java.sql.DataTruncation;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
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
	boolean shouldWait = false;
	Object stopMonitor = new Object();
	private boolean isConnected = false;
	Connection connection = null;



	public void loadDriver() throws ClassNotFoundException
	{
		if (!isDriverLoaded) {
			Class.forName(Configuration.getInstance().getDriver());
			isDriverLoaded = true;
		}
	}

	public void reportSQLException(SQLException ex)
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



	public void Connect() throws SQLException
	{
		//System.out.println("Open a connection.");
		connection = DriverManager.getConnection(Configuration.getInstance().getDNS());
		reportSQLWarning(connection.getWarnings());
		connection.setAutoCommit (false);
		isConnected = true;
	}




	public void Disconnect()
	{
		try {
			if (connection != null && connection.isClosed() == false) {
				// Close the connection
				CommitTransaction();
				//System.out.println("Close the connection.");
				connection.close();
			}
			isConnected = false;
		}  catch (SQLException ex) {
			reportSQLException(ex);
		}
	}


	public TTConnection() throws ClassNotFoundException
	{
		this.isDriverLoaded = false;
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

	private void CreateContracts() throws SQLException{
		if (isConnected == false) return;

		Statement s = connection.createStatement();

		//drop an recreate the table
		BeginTransaction();
		try {	s.execute("DROP INDEX ContractIdx");
		} catch (SQLException e){
		}
		try {	s.execute("DROP TABLE Contract");
		} catch (SQLException e){
		}
		CommitTransaction();

		s.execute("CREATE TABLE Contract (contractID INTEGER)");
		CommitTransaction();

		BeginTransaction();
		for (int i = 0; i < Configuration.getInstance().getMaxContracts(); i++) {
			s.execute("INSERT INTO Contract VALUES (" + i + ")");
			CommitTransaction();
		}
		s.execute("CREATE UNIQUE INDEX ContractIdx ON Contract (contractID)");

	}



	public void CreateTableStructure() throws SQLException {
		if (isConnected == false) return;
		System.out.println("Maybe create tables ... ");
		CreateContracts();
	}


	/**
	 * Reads all bundle instances for a given contract id
	 *
	 */
	public void executeRead (int contractID) {
		try {

			BeginTransaction();

			PreparedStatement pstmt=connection.prepareStatement("SELECT * FROM Contract where contractID=?");
			pstmt.setInt(1, contractID);

			ResultSet rs = pstmt.executeQuery();
			while ( rs.next() ) {
				//System.out.printf( "Found Contract: %s \n", rs.getInt(1));
			}

			reportSQLWarning(pstmt.getWarnings());
			pstmt.close();

			//RollbackTransaction();
		} catch (SQLException e) {
			reportSQLException(e);
		}
	}

}
