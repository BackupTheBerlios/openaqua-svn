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
final public class CTcpServer extends Thread {
	final Integer port;
	final ATcpCommand command;
	final ExecutorService executor = Executors.newCachedThreadPool(); 
	final ServerSocket serverSocket; 
	final private static Logger logger = Logger.getRootLogger();

	//no default constructor
	private CTcpServer()  {
		command = null;
		port = null;
		serverSocket = null;
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
				//get a Connect Context
				final CTcpConnectionContext conn = new CTcpConnectionContext();
				conn.setSocket(serverSocket.accept());
				
				//make up a runnable execution context
				Runnable r1 = new Runnable() {public void run() {command.execute(conn);}};
				
				//execute it in background
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
			
		} catch (Exception e) {
			logger.error("Got unknown exception: : "+e.getLocalizedMessage());
			e.printStackTrace();
			return;
		}
	}
}
