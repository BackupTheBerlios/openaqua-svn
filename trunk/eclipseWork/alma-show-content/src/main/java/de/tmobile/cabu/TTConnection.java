/**
 *
 */
package de.tmobile.cabu;

import java.sql.Connection;
import java.sql.DataTruncation;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.sql.SQLException;
import java.sql.SQLWarning;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;
import java.util.Map;

import org.apache.log4j.Logger;


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
	private Logger logger = Logger.getRootLogger();
	private Map<Integer, String> mapSubType;



	public TTConnection() throws ClassNotFoundException
	{
		this.mapSubType = new HashMap<Integer, String>();
		this.isDriverLoaded = false;
		loadDriver();
	}



	public void loadDriver() throws ClassNotFoundException
	{
		if (!isDriverLoaded) {
			Class.forName("com.timesten.jdbc.TimesTenDriver");
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



	public boolean Connect(final String dsn) {
		try {
			connection = DriverManager.getConnection(dsn);
			reportSQLWarning(connection.getWarnings());
			//connection.setAutoCommit (true);
			isConnected = true;
			BuildSubTypeDescription();
			return true;
		} catch (SQLException e) {
			isConnected = false;
			logger.error("Cannot Connect to DSN: "+dsn);
			reportSQLException(e);
			return false;
		}
	}




	public boolean Disconnect()
	{
		try {
			if (connection != null && connection.isClosed() == false) {
				connection.close();
			}
			isConnected = false;
			return true;
		}  catch (SQLException ex) {
			reportSQLException(ex);
			return false;
		}
	}
	
	
	public String GetSubTypeDescription(Integer id) {
		String result = "<unknown>";
		if (mapSubType.containsKey(id)) {
			result = mapSubType.get(id);
		}
		return result;
	}

	public void ListKnownSubTypes(){
		Iterator<Integer> it = mapSubType.keySet().iterator();
		while(it.hasNext()) {
			Integer id=it.next();
			logger.debug("Know Subtype "+id+"="+mapSubType.get(id));
		}
		
	}
	
	
	public void BuildSubTypeDescription() {
		if (isConnected == false) return ;
		mapSubType = new HashMap<Integer, String>();

		try {
			//exec SQL command
			Statement stmt;
			stmt = connection.createStatement();

			ResultSet rs = stmt.executeQuery("select sub.element_subtype_cv, desc.description from acm_schema.acm$ta_element_subtype_cv sub, acm_schema.acm$ta_description desc where sub.description_id=desc.description_id");   
			
			//parse the result
			while(rs.next()) {
				int id = rs.getInt(1);
				String element_value = rs.getString(2);
				mapSubType.put(id, element_value);
			}
			
			//close statements
			rs.close();
			stmt.close();
			
		} catch (SQLException e) {
			logger.error("Error while List Root ids for templates:");
			reportSQLException(e);
		}
		
	}
	 
	

	
	public void listTemplateDescription(Integer rootId) {
		
		if (isConnected == false) return ;

		try {
			//exec SQL command
			Statement stmt;
			stmt = connection.createStatement();
			
			ResultSet rs = stmt.executeQuery("select ELEMENT_TEMPLATE_ID, element_type_cv, element_subtype_cv, value  from acm_schema.acm$ta_element_tmpl where root_id = parent_id and root_id="+rootId);
			
			//parse the result
			while(rs.next()) {
				int element_id = rs.getInt(1);
				int element_type = rs.getInt(2);
				int element_subtype = rs.getInt(3);
				String element_value = rs.getString(4);
				logger.debug("Element Id="+element_id + " type="+element_type+" subtype("+element_subtype+")="+GetSubTypeDescription(element_subtype)+" value="+element_value);
			}
			
			//close statements
			rs.close();
			stmt.close();
			
		} catch (SQLException e) {
			logger.error("Error while List Root ids for templates:");
			reportSQLException(e);
		}
	}

	
	public void listTemplate(Integer elementId) {
		logger.debug("List Template for ID "+elementId);
		listTemplateDescription(elementId);
	}

	
	public void listAllTemplates(List<Integer> ids) {
		ListIterator<Integer> it = ids.listIterator();
		while(it.hasNext()) {
			listTemplate(it.next());
		}
	}

	
	public List<Integer> getTemplateIds() {
		List<Integer> result = new LinkedList<Integer>(); 
		if (isConnected == false) return result;
		
		try {
			//exec SQL command
			Statement stmt;
			stmt = connection.createStatement();
			ResultSet rs = stmt.executeQuery("select ELEMENT_TEMPLATE_ID from ACM_SCHEMA.ACM$TA_ELEMENT_TMPL where element_template_id = root_id order by ELEMENT_TEMPLATE_ID ; ");
			
			//parse the result
			while(rs.next()) {
				int element_id = rs.getInt(1);
				result.add(element_id);
			}
			
			//close statements
			rs.close();
			stmt.close();
			
		} catch (SQLException e) {
			logger.error("Error while List Root ids for templates:");
			reportSQLException(e);
		}
		return result;
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
