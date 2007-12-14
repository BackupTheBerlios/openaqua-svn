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
		if (CConfiguration.getInstance().isError()) { return; }
		try {
			list.refreshList();
		} catch (final SQLException e) {
			CConfiguration.getInstance().getConnection().reportSQLException(e);
			CConfiguration.getInstance().getConnection().Disconnect();
		}

	}


}
