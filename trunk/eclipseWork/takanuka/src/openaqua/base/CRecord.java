/**
 * 
 */
package openaqua.base;

/**
 * @author tukaram
 *
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
		return true;
	}
}
