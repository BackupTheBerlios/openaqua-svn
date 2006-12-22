package record;

public class CRecord {
	
	public int getValue() {
		return m_value;
	}
	
	public void setValue(int i) {
		m_value = i;
	}
	
	
	public String getRecordTypeString (){
		return "Detail";
	}
	
	public long getInt64 () {
		return 12345678L;
	}

	public String getString() {
		return "string";
	}

	private int m_value;

}
