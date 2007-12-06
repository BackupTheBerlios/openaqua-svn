/**
 * 
 */
package de.tmobile.cabu;


import java.sql.SQLException;


/**
 * @author behrenan
 * 
 */
public class AlmaListLoaderThread implements Runnable {
	final CBaseList list;

	public AlmaListLoaderThread(final CBaseList list) {
		this.list = list;
	}


	/* (non-Javadoc)
	 * @see java.lang.Runnable#run()
	 */
	public void run() {
		if (Configuration.getInstance().isError()) { return; }
		try {
			list.refreshList();
		} catch (final SQLException e) {
			Configuration.getInstance().getConnection().reportSQLException(e);
			Configuration.getInstance().getConnection().Disconnect();
		}

	}


}
