/**
 * 
 */
package openaqua.comm;


import java.net.*; 
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.io.*; 

import org.apache.log4j.Logger;

/**
 * The CTcpServer handles TCP/IP connections on a given port.
 * 
 * The class expects a port number and a ICommand the deal with new 
 * 
 */
//TODO how to inform other parts if an error happend

final public class CTcpServer extends Thread {
	Integer port = new Integer(0);
	final ATcpCommand command;
	ExecutorService executor = Executors.newCachedThreadPool(); 
	ServerSocket serverSocket = null; 
	private static Logger logger = Logger.getRootLogger();

	//no default constructor
	private CTcpServer()  {
		command = null;
	}
	
	
	/**
	 * 
	 * @param command the command which deals with incoming connections 
	 * @param port the port number a server is listening
	 * @throws IOException
	 */
	public CTcpServer(final ATcpCommand command, final int port)  throws IOException {
		super();
		this.command = command;
		this.port = port;
		serverSocket = new ServerSocket(port);
		logger.debug("TCP Server created to listen on port " + this.port.toString());
		//new Thread( this ).start(); 
	}

	/**
	 * @param command the command which deals with incoming connections 
	 * @param port the port number a server is listening
	 * @param backlog max number of possible waiting connections
	 * @throws IOException
	 */
	public CTcpServer(final ATcpCommand command, final int port, final int backlog)  throws IOException {
		super();
		this.command = command;
		this.port = port;
		serverSocket = new ServerSocket(port, backlog);
		logger.debug("TCP Server created to listen on port " + this.port.toString());
	    //new Thread( this ).start(); 
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
				CTcpConnectionContext conn = new CTcpConnectionContext();
				conn.setSocket(serverSocket.accept());
				Runnable r1 = new Runnable() { 
					public void run() {
						//TODO Add command execution
						//command.execute(conn);
						
					} 
				}; 		
				executor.execute(r1);
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
