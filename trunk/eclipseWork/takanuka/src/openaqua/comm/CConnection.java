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

	public CConnection(Socket socket) {
		super();
		this.socket = socket;
	}
	
	public IEvent clone() {
		return this;
	}

	/**
	 * Resets all internal data to an "empty" default state. That state might be different than
	 * the state which a record has after creation by a prototype factory
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
	 * The method must be overidden. Otherwise the default behaviour happes which
	 * simply compares the object reference.
	 * 
	 * @see {@link http://www.javaworld.com/javaqa/2002-06/01-qa-0621-hashtable.html} for
	 * detailed description about overriding.
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
