/**
 * 
 */
package openaqua.comm;

import java.io.IOException;
import java.net.Socket;
import org.apache.log4j.Logger;
import openaqua.base.IContext;

/**
 * @author behrenan
 *
 */
public class CTcpConnectionContext implements IContext {
	Socket socket = null;
	final private static Logger logger = Logger.getRootLogger();
	

	/**
	 * 
	 */
	public CTcpConnectionContext() {
		super();
	}

	
	
	/**
	 * @return return a new CConnection Record with an invalid socket!!!!
	 */
	public IContext clone() {
		
		return new CTcpConnectionContext();
	}
	
	
	/**
	 * 
	 * @return the socket itself
	 */
	public final Socket getSocket() {
		return socket;
	}

	/**
	 * 
	 * @return the socket itself
	 */
	public void setSocket(Socket socket) {
		this.socket = socket;
		
	}

	
	/**
	 * @return int with hashcode for this object
	 */
	public int hashCode() {
		int hashcode = "CTcpConnectionContext".toString().hashCode();
		hashcode = hashcode * socket.hashCode();
		return hashcode;
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
		if (!(object instanceof CTcpConnectionContext)) return false;
		CTcpConnectionContext o = (CTcpConnectionContext) object;
		if (o.socket.equals(this.socket) != true) return false; 
		return true;
	}
	

}
