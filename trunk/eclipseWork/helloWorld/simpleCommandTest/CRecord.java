package simpleCommandTest;

import openaqua.base.IRecord;

public class CRecord implements IRecord {
	private String m_str;
	
	String getString() {
		return m_str;
	}
	
	public IRecord clone() {
		CRecord clone = new CRecord();
		clone.setString(getString());
		return clone;		
	}

	public void setString(String m) {
		m_str = m;
	}
	
	public void reset() {
		m_str="";
	}
}
