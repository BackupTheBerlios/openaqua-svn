package openaqua.connector;

import openaqua.base.CFactoryCommands;
import openaqua.base.CFactoryRecords;
import openaqua.base.IRecord;

public class Connector {
	
	public Connector () {
		super();
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
		IRecord r = CFactoryRecords.getInstance().getRecord(1);
		boolean result = CFactoryCommands.getInstance().getCommand(6000).execute(r);
		return result;
	}

}
