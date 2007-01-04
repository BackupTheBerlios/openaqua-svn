/**
 * 
 */
package openaqua.comm;


import java.net.*; 
import java.io.*; 

import org.apache.log4j.Logger;

/**
 * @author behrenan
 * 
 */
//TODO how to inform other parts if an error happend

public class CTcpServer extends Thread {
	Integer port = new Integer(0);
	
	ServerSocket serverSocket = null; 
	private static Logger logger = Logger.getRootLogger();

	//no default constructor
	private CTcpServer()  {}
	
	
	/**
	 * 
	 * @param port the port number a server is listening
	 * @throws IOException
	 */
	public CTcpServer(final int port)  throws IOException {
		super();
		this.port = port;
		serverSocket = new ServerSocket(port);
		logger.debug("TCP Server created to listen on port " + this.port.toString());	
		this.start();
	}

	/**
	 * 
	 * @param port the port number a server is listening
	 * @param backlog max number of possible waiting connections
	 * @throws IOException
	 */
	public CTcpServer(final int port, final int backlog)  throws IOException {
		super();
		this.port = port;
		serverSocket = new ServerSocket(port, backlog);
		logger.debug("TCP Server created to listen on port " + this.port.toString());	
		this.start();
	}
	
	
	/**
	 * 
	 */
	@Override
	public void run ()   {
		if (serverSocket == null) throw new NullPointerException("Got null reference as socket");
		logger.debug("TCP Server listening on port " + port.toString());

		try {
			while(!isInterrupted()) {
				Socket socket = serverSocket.accept();
				//TODO add command?
				CTcpServerConnectionFactory.getInstance().execConnection(0, socket);
			}
		} catch ( ThreadDeath td ) {
			try { 
				serverSocket.close();
			} catch (IOException e) {
				logger.error("Error while closing TcpServerSocket: "+td.getLocalizedMessage());
				e.printStackTrace();
			}
			
		} catch (IOException e) {
			logger.error("Error while waiting for connections: : "+e.getLocalizedMessage());
			e.printStackTrace();
			return;
		}
		
	}
	
	
}
