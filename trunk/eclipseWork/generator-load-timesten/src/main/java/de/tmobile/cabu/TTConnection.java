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
	private PreparedStatement lookupForInstance = null;
	private PreparedStatement setLockForInstance = null;
	private Random random = new Random();
	
	


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
		connection.setAutoCommit (true);
		//lookupForInstance = connection.prepareStatement("select i.budgetinstance_id, i.alock, i.subscription_id, i.value from TA_BUDGET_instance i, TA_BUDGETSUBSCRIPTION s where s.CONTRACT_ID=? and s.subscription_id=i.subscription_id;");
		lookupForInstance = connection.prepareStatement("select i.budgetinstance_id, i.alock, i.value from TA_BUDGET_instance i, TA_BUDGETSUBSCRIPTION s " +
				"where s.CONTRACT_ID=? and s.subscription_id=i.subscription_id;");
		setLockForInstance = connection.prepareStatement("UPDATE TA_BUDGET_instance set alock=sysdate where budgetinstance_id=? ");
		isConnected = true;
	}




	public void Disconnect()
	{
		try {
			if (connection != null && connection.isClosed() == false) {
				lookupForInstance.close();
				setLockForInstance.close();
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

	public void CreateTableStructure() throws SQLException {
		if (isConnected == false) return;

		Statement s = connection.createStatement();

		System.out.println(" delete old data ... ");
		connection.setAutoCommit (false);
		
		s.execute("delete from TA_BUDGET_INSTANCE ;");
		s.execute("delete from TA_BUDGETSUBSCRIPTION ;");
		s.execute("delete from TA_BUDGET ;");
		s.execute("delete from TA_INSTANTIATION_TYPE ;");
		s.execute("delete from TA_CONTRACTS ;");
		
		System.out.println(" setup TA_CONTRACTS... ");
		for (int i = 0; i < Configuration.getInstance().getMaxContracts(); i++) {
			s.execute("insert into TA_CONTRACTS (CONTRACT_ID, VALID_FROM, VALID_TO, LAST_CHANGED) values (" + i + ", '2006-12-12 00:00:01', '2007-12-12 00:00:01', '2006-12-12 00:16:16');");
		}

		System.out.println(" setup TA_INSTANTIATION_TYPE... ");
		for (int i = 0; i < 50; i++) {
			s.execute("insert into TA_INSTANTIATION_TYPE (INST_TYPE_ID, DESCRIPTION) values ("+i+", 'foo');");
		}
		
		System.out.println(" setup TA_BUDGET... ");
		for (int i = 0; i < 200; i++) {
			s.execute("insert into TA_BUDGET (BUDGET_ID, INST_TYPE_ID, INITIAL_VALUE, UNIT, INSTANTIATION_TYPE) values ("+i+", 1, 1234, 50, 50);");
		}

		System.out.println(" setup TA_BUDGETSUBSCRIPTION... ");
		for (int i = 0; i < Configuration.getInstance().getMaxSubsriptions(); i++) {
			int contractID = Math.abs(random.nextInt()) % Configuration.getInstance().getMaxContracts();
			int budgetID =  Math.abs(random.nextInt()) % 200;
			s.execute("insert into TA_BUDGETSUBSCRIPTION (SUBSCRIPTION_ID, CONTRACT_ID, BUDGET_ID, VALID_FROM) values ("+i+", "+contractID+", "+budgetID+", '2006-12-12 00:00:01');");
		}
		
		System.out.println(" setup TA_BUDGET_INSTANCE... ");
		for (int i = 0; i < Configuration.getInstance().getMaxInstances(); i++) {
			int subID =  Math.abs(random.nextInt()) % Configuration.getInstance().getMaxSubsriptions();
			s.execute("insert into TA_BUDGET_INSTANCE (SUBSCRIPTION_ID, BUDGETINSTANCE_ID, VALID_FROM, VALID_TO, ALOCK, VALUE) values ("+subID+", "+i+", '2006-12-12 00:00:01', '2007-12-12 00:00:01', NULL,  "+i+");");
		}
		connection.commit();
		connection.setAutoCommit(true);
	}


	/**
	 * Reads all bundle instances for a given contract id
	 *
	 */
	public void executeRead (int contractID) {
		try {
			
			//BeginTransaction();
			lookupForInstance.setInt(1, contractID);
			ResultSet rs = lookupForInstance.executeQuery();
			while ( rs.next() ) {
				setLockForInstance.setInt(1, rs.getInt(1));
				setLockForInstance.execute();
				//CommitTransaction();
			}
			
		} catch (SQLException e) {
			System.out.println("Lock-Error?: "+e.getMessage());
			//reportSQLException(e);
		}
		return;
	}

}
