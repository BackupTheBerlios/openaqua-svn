/**
 * 
 */
package openaqua.comm;

import java.net.Socket;

/**
 * @author behrenan
 *
 */
public class CTcpServerConnection extends Thread implements ITcpServerConnection  {
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
