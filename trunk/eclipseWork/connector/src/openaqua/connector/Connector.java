package openaqua.connector;

import openaqua.base.CFactoryCommands;
import openaqua.base.ICommand;

import java.io.IOException;
import java.util.concurrent.ExecutorService; 
import java.util.concurrent.Executors; 

import org.apache.log4j.Logger;

import openaqua.base.CFactoryContexts;
import openaqua.comm.ATcpCommand;
import openaqua.comm.CTcpServer;
public class Connector extends Thread{
	private CTcpServer serverEcho;
	private static Logger logger = Logger.getRootLogger();

	/**
	 * Executor Service, handles a thread pool for threaded command execution
	 */
	ExecutorService executor = Executors.newCachedThreadPool();

	public Connector () {
		super();
        CFactoryCommands.getInstance().registerBuilder(new CConnectorCommandBuilder());
        //CFactoryContexts.getInstance().addRecordPrototyp(1, new CTcpConnectionContext());
        CFactoryContexts.getInstance().addRecordPrototyp(2, new ClientRecord());
        setupTcpServer();
	}
	
	/**
	 * Setup the TcpServer Thread
	 *
	 */
	private void setupTcpServer() {
        ICommand i = CFactoryCommands.getInstance().getCommand(5001);
        if (i instanceof ATcpCommand) {
        	try {
        		serverEcho = new CTcpServer("EchoServer", 5001, 12345);
        	} catch (IOException e) {
        		logger.error("Got IOException while creating CTcpServer: " + e.getLocalizedMessage());
        		e.printStackTrace();
    			throw new IllegalArgumentException("Command 5001 is not a ATcpCommand");
        	}
        	
		} else {
			throw new IllegalArgumentException("Command 5001 is not a ATcpCommand");
		}
	}
	
	
	public void start() {
		serverEcho.start();
	}

	public void run () {
		;//nothing to do. But let the sub threads do their job
	}
}
