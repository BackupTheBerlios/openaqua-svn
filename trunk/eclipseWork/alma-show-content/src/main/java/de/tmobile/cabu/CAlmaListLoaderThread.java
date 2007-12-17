/**
 * 
 */
package de.tmobile.cabu;


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
		final TTConnection connection = CConfiguration.getInstance().getConnection(list);
		if (!connection.isConnected()) { return; }
		try {
			list.refreshList();
		} catch (final SQLException e) {
			TTConnection.reportSQLException(e);
			connection.Disconnect();
		}
		CLogger.getRootLogger().debug("End   RUN for " + list.getClass().getCanonicalName());
	}
}
