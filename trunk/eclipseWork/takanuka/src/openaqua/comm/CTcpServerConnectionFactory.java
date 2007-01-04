/**
 * 
 */
package openaqua.comm;

import java.net.Socket;

/**
 * @author behrenan
 *
 */
public class CTcpServerConnectionFactory {
	final private static CTcpServerConnectionFactory INSTANCE = new CTcpServerConnectionFactory();
	
	/**
	 * 
	 * @return the reference to the singleton instance
	 */
	final public static CTcpServerConnectionFactory  getInstance() {
		return INSTANCE;
	}
	
	/**
	 * private default constructor
	 *
	 */
	private CTcpServerConnectionFactory () {
		
	}
	
	/**
	 * 
	 */
	public void execConnection(final int type, final Socket sock){
		CTcpServerConnection c = new CTcpServerConnection (sock);
		//c.start();
	}
	

}
