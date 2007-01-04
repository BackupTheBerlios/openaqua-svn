/**
 * 
 */
package openaqua.comm;

import java.io.IOException;
import java.net.Socket;
import org.apache.log4j.Logger;
import openaqua.base.IEvent;

/**
 * @author behrenan
 *
 */
public class CConnection implements IEvent {
	final Socket socket;
	final private static Logger logger = Logger.getRootLogger();
	

	/**
	 * 
	 */
	private CConnection() {
		super();
		socket = null;
	}

	
	/**
	 * 
	 * @param socket - reference to a socket. 
	 */
	public CConnection(Socket socket) {
		super();
		this.socket = socket;
	}

	
	
	/**
	 * @return return a new CConnection Record with an invalid socket!!!!
	 */
	public IEvent clone() {
		return new CConnection(null);
	}
	
	
	/**
	 * 
	 * @return the socket itself
	 */
	public final Socket getSocket() {
		return socket;
	}

	
	
	/**
	 * Resets all internal data to an "empty" default state. That state might be different than
	 * the state which a record has after creation by a prototype factory<br>
	 * 
	 * Specially: A call close(!) the socket
	 *
	 */
	public void reset()  {
		try {
			socket.close();
		} catch (IOException e) {
			logger.error("Error while closing TcpServerSocket: "+e.getLocalizedMessage());
			e.printStackTrace();
		}
		
	}
	
	/**
	 * Compares two objects and compares all internal values.<br>
	 * 
	 * @param object the object which has to be compared
	 * @return true = the object are equal
	 */
	public boolean equals(java.lang.Object object) {
		if (this == object) return true;
		if (!(object instanceof CConnection)) return false;
		CConnection o = (CConnection) object;
		if (o.socket.equals(this.socket) != true) return false; 
		return true;
	}
	

}
