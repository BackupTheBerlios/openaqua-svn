package openaqua.connector;

import openaqua.base.CFactoryCommands;
import java.util.concurrent.ExecutorService; 
import java.util.concurrent.Executors; 
import openaqua.base.CFactoryRecords;
import openaqua.base.IEvent;
public class Connector {
	/**
	 * class is a singleton
	 */
	final private static Connector INSTANCE = new Connector();

	/**
	 * Executor Service, handles a thread pool for threaded command execution
	 */
	ExecutorService executor;

	public Connector () {
		super();
		executor = Executors.newCachedThreadPool();
		Init();
	}

	
	/** 
	 * 
	 * @return a reference to a singleton instance of this factory
	 */
	final public static Connector getInstance() {
		return INSTANCE;
	}
	
	
	/**
	 * Init the Connector object
	 * @return true if successfull
	 */
	public boolean Init() {
		//register the project Command builder
        CFactoryCommands.getInstance().registerBuilder(new CConnectorCommandBuilder());
        
        //register default ClientRecord at record factory
        CFactoryRecords.getInstance().addRecordPrototyp(1, new ClientRecord());
        
		return true;
	}
	
	public boolean ExecuteUidMacro() {
		IEvent r = CFactoryRecords.getInstance().getRecord(1);
		boolean result = CFactoryCommands.getInstance().getCommand(6000).execute(r);
		return result;
	}

}
