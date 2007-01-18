package de.openaqua.base;

/**
 * @author tukaram
 */
public class CRecord implements IContext {
	public CRecord(){
		super();
	}

	/**
	 * Should create a clone of a record
	 */
	public IContext clone() {
		return new CRecord();
	}

	public int hashCode() {
		return "openaqua.base.CRecord".hashCode();
	}


	public void reset() {
		;//default implementation is empty
	}


	public boolean equals(java.lang.Object object) {
		if (this == object) return true;
		if (!(object instanceof CRecord)) return false;
		//in real world you would need the comparing (or unsing of equals again)
		//of internal variables
		return true;
	}
}
