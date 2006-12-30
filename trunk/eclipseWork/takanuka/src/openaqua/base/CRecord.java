/**
 * 
 */
package openaqua.base;

/**
 * @author tukaram
 * TODO  class needs a hashCode() implemenation 
 */
public class CRecord implements IRecord {
	public CRecord(){
		super();
	}

	/**
	 * Should create a clone of a record
	 */
	public IRecord clone() {
		return new CRecord();
	}


	public void reset() {
		//default implementation is empty
	}
	
	
	public boolean equals(java.lang.Object object) {
		if (this == object) return true;
		if (!(object instanceof CRecord)) return false;
		//in real world you would need the comparing (or unsing of equals again)
		//of internal variables
		return true;
	}
}
