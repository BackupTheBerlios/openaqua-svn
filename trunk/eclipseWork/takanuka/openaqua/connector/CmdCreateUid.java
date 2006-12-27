package openaqua.connector;

import java.net.InetAddress;
import java.net.UnknownHostException;
import java.rmi.server.UID;

import org.apache.log4j.Logger;

import openaqua.base.ICommand;
import openaqua.base.IRecord;

public class CmdCreateUid implements ICommand {
	private static Logger logger = Logger.getRootLogger();


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
			logger.debug("UID="+id);
			String host = "";
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
