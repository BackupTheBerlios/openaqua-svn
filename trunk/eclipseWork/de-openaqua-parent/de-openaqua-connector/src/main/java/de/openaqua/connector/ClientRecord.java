package de.openaqua.connector;
import de.openaqua.base.IContext;


public class ClientRecord implements IContext {
	private String clientId;

	/**
	 * Default Constructor
	 *
	 */
	public ClientRecord() {
		super();
		this.clientId = "";
	}



	/**
	 * Makes a deep copy of a Record
	 */
	@Override
	public IContext clone() {
		ClientRecord r = new ClientRecord();
		r.setClientId(this.clientId);
		return r;
	}


	public void reset() {
		this.clientId = "";
	}



	/**
	 * @return the clientId
	 */
	public synchronized final String getClientId() {
		return this.clientId;
	}



	/**
	 * @param clientId the clientId to set
	 */
	public synchronized final void setClientId(String clientId) {
		this.clientId = clientId;
	}

	public String toString() {
		return "ClientRecord(clientId='" + clientId + "')";
	}

}
