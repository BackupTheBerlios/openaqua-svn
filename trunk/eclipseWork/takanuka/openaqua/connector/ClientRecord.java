package openaqua.connector;
import openaqua.base.IRecord;


public class ClientRecord implements IRecord {
	private String clientId; 
	
	/**
	 * Default Constructor
	 *
	 */
	public ClientRecord() {
		super();
		clientId = "";
	}
	
	
	
	/**
	 * Makes a deep copy of a Record 
	 */
	@Override
	public IRecord clone() {
		ClientRecord r = new ClientRecord();
		r.setClientId(clientId);
		return r;
	}

	
	public void reset() {
		clientId = "";
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
