/**
 * 
 */
package openaqua.comm;

import java.net.Socket;

/**
 * @author behrenan
 *
 */
public class CTcpServerConnection  {
	final private Socket socket;
	
	
	private CTcpServerConnection () {
		super();
		socket = null;		
	}
	
	public CTcpServerConnection(Socket sock) {
		super();
		socket = sock;
	}
	
	

}
