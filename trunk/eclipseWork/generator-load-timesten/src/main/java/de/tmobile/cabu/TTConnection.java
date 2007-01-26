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
	private PreparedStatement lookupForInstanceForUpdate = null;
	private PreparedStatement setLockForInstance = null;
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
		//connection = DriverManager.getConnection(Configuration.getInstance().getDNS(), "ALMGR_SCHEMA", "perf20tst");
		reportSQLWarning(connection.getWarnings());
		connection.setAutoCommit (false);

		lookupForInstance = connection.prepareStatement("select budgetinstance_id, alock, value from TA_BUDGET_instance where CONTRACT_ID=?");

		lookupForInstanceForUpdate = connection.prepareStatement("select budgetinstance_id, alock, value from TA_BUDGET_instance where CONTRACT_ID=? for update");
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



	public void CreateTableStructure() throws SQLException {
		if (isConnected == false) return;

		Statement s = connection.createStatement();

		System.out.println(" delete old data ... ");
		connection.setAutoCommit (false);

		try {s.execute("drop table TA_BUDGET_INSTANCE");}catch(SQLException e) {;}
		try {s.execute("drop table TA_BUDGETSUBSCRIPTION");}catch(SQLException e) {;}
		try {s.execute("drop table TA_CONTRACTS");}catch(SQLException e) {;}
		try {s.execute("drop table TA_BUDGET");}catch(SQLException e) {;}
		try {s.execute("drop table TA_INSTANTIATION_TYPE");}catch(SQLException e) {;}


		s.execute("create table TA_INSTANTIATION_TYPE (INST_TYPE_ID  SMALLINT not null)");



		s.execute("create table TA_BUDGET ("+
				"BUDGET_ID            SMALLINT                       not null,"+
				"INST_TYPE_ID         SMALLINT                       not null,"+
				"INITIAL_VALUE        SMALLINT                       not null,"+
				"UNIT                 SMALLINT                       not null"+		")");



		s.execute("create table TA_CONTRACTS ("+
				"CONTRACT_ID          INTEGER                         not null,"+
				"VALID_FROM           TIMESTAMP                       not null,"+
				"VALID_TO             TIMESTAMP,"+
				"LAST_CHANGED         TIMESTAMP"+		")");



		s.execute("create table TA_BUDGETSUBSCRIPTION ("+
				"SUBSCRIPTION_ID      INTEGER                         not null,"+
				"CONTRACT_ID          INTEGER                         not null,"+
				"BUDGET_ID            SMALLINT                        not null,"+
				"VALID_FROM           TIMESTAMP                       not null"+		")");

/*
		s.execute("create table TA_BUDGET_INSTANCE ("+
				"BUDGETINSTANCE_ID    INTEGER                         not null,"+
				//"DESCRIPTION          CHAR(30),  "+
				"SUBSCRIPTION_ID      INTEGER                         not null,"+
				"CONTRACT_ID          INTEGER                         not null,"+
				"VALID_FROM           TIMESTAMP,"+
				"VALID_TO             TIMESTAMP,"+
				"ALOCK                TIMESTAMP,"+
				"VALUE                SMALLINT"+		
				")");
*/

		s.execute("CREATE TABLE TA_BUDGET_INSTANCE 	("+
				"BUDGETINSTANCE_ID    INTEGER                         not null,"+
				"SUBSCRIPTION_ID      INTEGER                         not null,"+
				"CONTRACT_ID          INTEGER                         not null,"+
				"VALID_FROM           TIMESTAMP,"+
				"VALID_TO             TIMESTAMP,"+
				"ALOCK                TIMESTAMP,"+
				"VALUE                SMALLINT"+
				")"		        
		);
		
		/*

		s.execute("delete from TA_BUDGET_INSTANCE");
		s.execute("delete from TA_BUDGETSUBSCRIPTION");
		s.execute("delete from TA_BUDGET");
		s.execute("delete from TA_INSTANTIATION_TYPE");
		s.execute("delete from TA_CONTRACTS");

		System.out.println(" setup TA_CONTRACTS... ");
		PreparedStatement s1 = connection.prepareStatement("insert into TA_CONTRACTS (CONTRACT_ID, VALID_FROM, VALID_TO, LAST_CHANGED) values (?, '2006-12-12 00:00:01', '2007-12-12 00:00:01', '2006-12-12 00:16:16');");
		for (int i = 0; i < Configuration.getInstance().getMaxContracts(); i++) {
			s1.setInt(1, i);
			s1.execute();
		}
		//s.execute("create unique index contract_idx on  TA_CONTRACTS (CONTRACT_ID)");




		System.out.println(" setup TA_INSTANTIATION_TYPE... ");
		for (int i = 0; i < 50; i++) {
			s.execute("insert into TA_INSTANTIATION_TYPE (INST_TYPE_ID) values ("+i+");");
		}
		//s.execute("create unique index inst_idx on  TA_INSTANTIATION_TYPE (INST_TYPE_ID)");



		System.out.println(" setup TA_BUDGET... ");
		for (int i = 0; i < 200; i++) {
			s.execute("insert into TA_BUDGET (BUDGET_ID, INST_TYPE_ID, INITIAL_VALUE, UNIT) values ("+i+", 1, 1234, 50);");
		}
		//s.execute("create unique index budg_idx on  TA_BUDGET (BUDGET_ID)");



		System.out.println(" setup TA_BUDGETSUBSCRIPTION... ");
		PreparedStatement s4 = connection.prepareStatement("insert into TA_BUDGETSUBSCRIPTION (SUBSCRIPTION_ID, CONTRACT_ID, BUDGET_ID, VALID_FROM) values (?, ?, ?, '2006-12-12 00:00:01');");
		for (int i = 0; i < Configuration.getInstance().getMaxSubsriptions()*10; i++) {
			s4.setInt(1, i);
			s4.setInt(2, Math.abs(random.nextInt()) % Configuration.getInstance().getMaxContracts());
			s4.setInt(3, Math.abs(random.nextInt()) % 200);
			s4.execute();
		}
		//s.execute("create unique index budgs1_idx on TA_BUDGETSUBSCRIPTION (SUBSCRIPTION_ID)");
		//s.execute("create index budgs2_idx on TA_BUDGETSUBSCRIPTION (CONTRACT_ID )");

		 */
		System.out.println(" setup TA_BUDGET_INSTANCE... ");
		//PreparedStatement s5 = connection.prepareStatement("insert into TA_BUDGET_INSTANCE (BUDGETINSTANCE_ID, SUBSCRIPTION_ID, CONTRACT_ID, VALID_FROM, VALID_TO, ALOCK, VALUE) values (?, ?, ?, to_date('2006-12-12 00:00:01','YYYY-MM-DD HH24:MI:SS'), to_date('2007-12-12 00:00:01','YYYY-MM-DD HH24:MI:SS'), NULL, ?)");
		PreparedStatement s5 = connection.prepareStatement("insert into TA_BUDGET_INSTANCE (BUDGETINSTANCE_ID, SUBSCRIPTION_ID, CONTRACT_ID, VALID_FROM, VALID_TO, ALOCK, VALUE) values (?, ?, ?, '2006-12-12 00:00:01', '2007-12-12 00:00:01', NULL, ?)");
		for (int i = 0; i < Configuration.getInstance().getMaxInstances(); i++) {
			s5.setInt(1, i);
			s5.setInt(2, Math.abs(random.nextInt()) % Configuration.getInstance().getMaxSubsriptions());
			s5.setInt(3, Math.abs(random.nextInt()) % Configuration.getInstance().getMaxContracts());
			s5.setInt(4, Math.abs(random.nextInt()) % 200);
			s5.execute();
		}
		s.execute("create unique index budgi1_idx on  TA_BUDGET_INSTANCE (BUDGETINSTANCE_ID)");
		s.execute("create index budgi3_idx on  TA_BUDGET_INSTANCE (CONTRACT_ID)");


		connection.commit();
		connection.setAutoCommit(true);
	}


	/**
	 * Reads all bundle instances for a given contract id
	 *
	 */
	public void executeRead (int contractID) {
		try {
			lookupForInstance.setInt(1, contractID);
			ResultSet rs = lookupForInstance.executeQuery();
			while ( rs.next() ) {
				//System.out.println("read: "+i);
			}

		} catch (SQLException e) {
			System.err.println("RLock-Error?: "+e.getMessage());
			//reportSQLException(e);
		}
		return;
	}

	public void executeWrite (int contractID) {
		try {
			lookupForInstanceForUpdate.setInt(1, contractID);
			ResultSet rs = lookupForInstanceForUpdate.executeQuery();
			while ( rs.next() ) {
				setLockForInstance.setInt(1, rs.getInt(1));
				setLockForInstance.execute();
				//System.out.println("updated: "+rs.getInt(1));
			}
			connection.commit();

		} catch (SQLException e) {
			System.err.println("Lock-Error?: "+e.getMessage());
			reportSQLException(e);
		}
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
