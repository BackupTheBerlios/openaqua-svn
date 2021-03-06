package de.openaqua.connector;

import java.net.InetAddress;
import java.net.UnknownHostException;
import java.rmi.server.UID;
import de.openaqua.base.ICommand;
import de.openaqua.base.IContext;

public class CmdCreateUid implements ICommand {


	/**
	 * Create a global unique ID and store it in a ClientRecord
	 * @param context
	 * @return true if execution went fine
	 */
	public boolean execute (final IContext context) {
		boolean result = false;

		if (context instanceof ClientRecord) {
			ClientRecord client = (ClientRecord) context;
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
