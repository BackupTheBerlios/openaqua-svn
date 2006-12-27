package connector;

public class GetUidImpl extends _GetUidStub {
	final static long serialVersionUID = 0;
	private String _uid = "";
	
	
	public GetUidImpl(String uid) {
		super();
		_uid = uid;		
	}
	
	public static long getSerialVersionUID() {
		return serialVersionUID;
	}
	
	public String get_uid() {
		return _uid;
	}
	
	public void set_uid(String _uid) {
		this._uid = _uid;
	}
	

}
