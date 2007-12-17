/**
 * 
 */
package de.tmobile.cabu;


import java.util.HashMap;
import java.util.concurrent.locks.ReentrantLock;


/**
 * @author behrenan
 * 
 */
final public class CConfiguration {
	final private static CConfiguration INSTANCE = new CConfiguration();

	/*
	 * @result returns a object reference to this singleton
	 */
	final public static CConfiguration getInstance() {
		return INSTANCE;
	}

	private final HashMap<BaseList, TTConnection> base2connection = new HashMap<BaseList, TTConnection>();
	private final ReentrantLock mapLock = new ReentrantLock();
	private String connectionDriver;
	private String connectionDsn;

	private CConfiguration() {
		super();
	}

	/**
	 * @return the connection
	 */
	final public TTConnection getConnection(final BaseList base) {
		mapLock.lock();
		try {
			if (base2connection.containsKey(base)) {
				return base2connection.get(base);
			} else {
				final TTConnection connection = new TTConnection(connectionDriver);
				connection.Connect(connectionDsn);
				base2connection.put(base, connection);
				return connection;
			}
		} catch (final ClassNotFoundException e) {
			CLogger.getRootLogger().error("Cannot connect: " + e.getMessage());
			e.printStackTrace();
			return null;
		} finally {
			mapLock.unlock();
		}
	}


	/**
	 * @param connectionDriver
	 *           the connectionDriver to set
	 */
	public void setConnectionDriver(final String connectionDriver) {
		this.connectionDriver = connectionDriver;
	}

	/**
	 * @param connectionDsn
	 *           the connectionDsn to set
	 */
	public void setConnectionDsn(final String connectionDsn) {
		this.connectionDsn = connectionDsn;
	}
}
