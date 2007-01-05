/**
 * 
 */
package openaqua.comm;


import java.net.*; 
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.io.*; 
import openaqua.base.CRunnableCommand;

import org.apache.log4j.Logger;

/**
 * The CTcpServer handles TCP/IP connections on a given port.
 * 
 * The class expects a port number and a ICommand the deal with new 
 * 
 */
final public class CTcpServer extends Thread {
	final Integer port;
	final Integer commandId;
	final ExecutorService executor = Executors.newCachedThreadPool(); 
	final ServerSocket serverSocket; 
	final private static Logger logger = Logger.getRootLogger();

	/**
	 * no default constructor
	 */
	private CTcpServer()  {
		this.commandId = null;
		this.port = null;
		this.serverSocket = null;
	}
	
	
	/**
	 * 
	 * @param commandId the command which deals with incoming connections 
	 * @param port the port number a server is listening
	 * @throws IOException
	 */
	public CTcpServer(final String name, final int commandId, final int port)  throws IOException {
		super();
		this.commandId = commandId;
		this.port = port;
		this.serverSocket = new ServerSocket(port);
		setName(name);
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
				CRunnableCommand cmd = new CRunnableCommand(commandId, conn);

				//execute it in background
				executor.execute(cmd);
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
