package openaqua.connector;

import openaqua.base.CFactoryCommands;
import openaqua.base.ICommand;

import java.io.IOException;
import java.util.concurrent.ExecutorService; 
import java.util.concurrent.Executors; 

import org.apache.log4j.Logger;

import openaqua.base.CFactoryRecords;
import openaqua.comm.ATcpCommand;
import openaqua.comm.CTcpConnectionContext;
import openaqua.comm.CTcpServer;
public class Connector extends Thread{
	/**
	 * class is a singleton
	 */
//	final private static Connector INSTANCE = new Connector();
	final private CTcpServer server;
	private static Logger logger = Logger.getRootLogger();

	/**
	 * Executor Service, handles a thread pool for threaded command execution
	 */
	ExecutorService executor;

	public Connector () {
		super();
		executor = Executors.newCachedThreadPool();
        CFactoryCommands.getInstance().registerBuilder(new CConnectorCommandBuilder());
        CFactoryRecords.getInstance().addRecordPrototyp(1, new CTcpConnectionContext());
        ICommand i = CFactoryCommands.getInstance().getCommand(5001);
        if (i instanceof ATcpCommand) {
        	try {
        		server = new CTcpServer(new CmdTcpConnection(), 12345);
        	} catch (IOException e) {
        		logger.error("Got IOException while creating CTcpServer: " + e.getLocalizedMessage());
        		e.printStackTrace();
    			throw new IllegalArgumentException("Command 5001 is not a ATcpCommand");
        	}
        	
		} else {
			throw new IllegalArgumentException("Command 5001 is not a ATcpCommand");
		}
	}

	
	/** 
	 * 
	 * @return a reference to a singleton instance of this factory
	 */
//	final public static Connector getInstance() {
	//		return INSTANCE;
	//	}
	
	public void run () {
		server.run();
	}
}
