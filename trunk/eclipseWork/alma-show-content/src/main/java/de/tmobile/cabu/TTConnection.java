/**
 *
 */
package de.tmobile.cabu;

import java.sql.Connection;
import java.util.Random;
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
	private boolean isConnected = false;
	private Connection connection = null;
	private PreparedStatement statementGetAllTemplates= null;
	private Random random = new Random();


	public TTConnection() throws ClassNotFoundException
	{
		this.isDriverLoaded = false;
		loadDriver();
	}



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
		connection = DriverManager.getConnection(Configuration.getInstance().getDNS());
		reportSQLWarning(connection.getWarnings());
		connection.setAutoCommit (true);

		//lookupForInstance = connection.prepareStatement("select budgetinstance_id, alock, value from TA_BUDGET_instance where CONTRACT_ID=?");
		//setLockForInstance = connection.prepareStatement("UPDATE TA_BUDGET_instance set alock=sysdate where budgetinstance_id=? ");

		isConnected = true;
	}




	public void Disconnect()
	{
		try {
			if (connection != null && connection.isClosed() == false) {
				//lookupForInstance.close();
				//setLockForInstance.close();
				connection.close();
			}
			isConnected = false;
		}  catch (SQLException ex) {
			reportSQLException(ex);
		}
	}



	/**
	 * Reads all bundle instances for a given contract id
	 *
	 */
	public void executeRead (int contractID) {
		/*
		try {
			lookupForInstance.setInt(1, contractID);
			ResultSet rs = lookupForInstance.executeQuery();
			while ( rs.next() ) {
				//System.out.println("read: "+contractID);
				byte[] rawBuffer1 = rs.getBytes("var1");
				byte[] rawBuffer2 = rs.getBytes("var2");
				int k=0;
				for (int i=0; i<1024;i++) {
					k=rawBuffer1[i]+k;
					k=rawBuffer2[i]+k;
				}
				if (k==123) {
					System.out.println("k=123");
				}
			}

		} catch (SQLException e) {
			System.err.println("RLock-Error?: "+e.getMessage());
			reportSQLException(e);
		}*/
		return;
	}

	public void executeWrite (int contractID) {
		/*
		try {
			
			byte[] rawBuffer1 = new byte[ 1024 ];
			byte[] rawBuffer2 = new byte[ 1024 ];
			int j;
			j = 5;	for (int i = 0;i<1024;i++) {rawBuffer1[i]=(byte) j++;	if (j>=255)j=0;		}
			j = 5;	for (int i = 0;i<1024;i++) {rawBuffer2[i]=(byte) j++;	if (j>=255)j=0;		}
			setLockForInstance.setBytes(1, rawBuffer1);
			setLockForInstance.setBytes(2, rawBuffer2);
			setLockForInstance.setLong(3, contractID);
			setLockForInstance.execute();

		} catch (SQLException e) {
			System.err.println("RLock-Error?: "+e.getMessage());
			reportSQLException(e);
		}
		*/
		return;
	}

	/**
	 * @return the isDriverLoaded
	 */
	public final boolean isDriverLoaded() {
		return isDriverLoaded;
	}

	/**
	 * @param isDriverLoaded the isDriverLoaded to set
	 */
	public final void setDriverLoaded(boolean isDriverLoaded) {
		this.isDriverLoaded = isDriverLoaded;
	}
}
