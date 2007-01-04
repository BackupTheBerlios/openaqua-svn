package simpleCommandTest;

import openaqua.base.IContext;

public class CRecord implements IContext {
	private String m_str;
	
	String getString() {
		return m_str;
	}
	
	public IContext clone() {
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
