package openaqua.connector;

import java.net.InetAddress;
import java.net.UnknownHostException;
import java.rmi.server.UID;
import openaqua.base.ICommand;
import openaqua.base.IRecord;

public class CmdCreateUid implements ICommand {


	/**
	 * Create a global unique ID and store it in a ClientRecord
	 * @param record
	 * @return
	 */
	public boolean execute (final IRecord record) {
		boolean result = false;
		
		if (record instanceof ClientRecord) {
			ClientRecord client = (ClientRecord) record;
			UID id = new UID();
			String host;
			try {
				host = InetAddress.getLocalHost().getHostAddress().toString();
			} catch (UnknownHostException ex) {
				host = "127.0.0.1";
			}
			client.setClientId(id + "@" + host);
			result = true;
		}
		
		
		return result;
	}
	

}
