package openaqua.connector;

import java.io.IOException;
import java.util.concurrent.ExecutorService; 
import java.util.concurrent.Executors; 
import org.apache.log4j.Logger;
import openaqua.base.CFactoryContexts;
import openaqua.base.CFactoryCommands;
import openaqua.base.ICommand;
import openaqua.comm.ATcpCommand;
import openaqua.comm.CTcpServer;


final public class Connector extends Thread{
	private CTcpServer serverEcho;
	private static Logger logger = Logger.getRootLogger();

	/**
	 * Executor Service, handles a thread pool for threaded command execution
	 */
	ExecutorService executor = Executors.newCachedThreadPool();

	/**
	 * The constructor
	 *
	 */
	public Connector () {
		super();
		//register project specific command builder
        CFactoryCommands.getInstance().registerBuilder(new CConnectorCommandBuilder());
        
        //register project specific Context object prototypes
        CFactoryContexts.getInstance().addRecordPrototyp(2, new ClientRecord());
        
        //setup the TcpServer Thread
        setupEchoTcpServer();
	}
	
	/**
	 * Setup the TcpServer Thread
	 *
	 */
	private void setupEchoTcpServer() {
		//check whether there is a correct command
        ICommand i = CFactoryCommands.getInstance().getCommand(5001);
        if (i instanceof ATcpCommand) {
        	try {
        		//setup the server
        		serverEcho = new CTcpServer("EchoTcpServer", 5001, 12345);

        	} catch (IOException e) {
        		//if error while start up of the server thread
        		logger.error("Got IOException while creating CTcpServer: " + e.getLocalizedMessage());
        		e.printStackTrace();
    			throw new IllegalArgumentException("Command 5001 is not a ATcpCommand");
        	}
        	
		} else {
			throw new IllegalArgumentException("Command 5001 is not a ATcpCommand");
		}
	}
	
	
	/**
	 * start all subthreads
	 */
	public void start() {
		serverEcho.start();
	}

	
	/**
	 * The thread execution method
	 */
	public void run () {
		;//nothing to do. But the sub threads do the job
	}
}
