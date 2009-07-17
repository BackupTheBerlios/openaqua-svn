/**
 * 
 */
package de.openaqua.vwl;


import java.sql.SQLException;


/**
 * @author behrenan
 * 
 */
public class CAlmaListLoaderThread implements Runnable {
	final BaseList list;

	public CAlmaListLoaderThread(final BaseList list) {
		super();
		this.list = list;
	}


	public void run() {
		CLogger.getRootLogger().debug("Begin RUN for " + list.getClass().getCanonicalName());
		TTConnection connection = null;

		try {
			connection = new TTConnection(CConfiguration.getInstance().getConnectionDriver());
			connection.Connect(CConfiguration.getInstance().getConnectionDsn());
			if (!connection.isConnected()) { return; }
			list.refreshList(connection);
			connection.Disconnect();
			CLogger.getRootLogger().debug("End   RUN for " + list.getClass().getCanonicalName());

		} catch (final ClassNotFoundException e1) {
			CLogger.getRootLogger().error("Cannot Load Database Driver: " + e1.getLocalizedMessage());
			e1.printStackTrace();

		} catch (final SQLException e) {
			TTConnection.reportSQLException(e);
			if (connection != null) {
				connection.Disconnect();
			}
		}
	}
}
