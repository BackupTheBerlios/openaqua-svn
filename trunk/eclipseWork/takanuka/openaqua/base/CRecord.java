/**
 * 
 */
package openaqua.base;

/**
 * @author tukaram
 *
 */
public class CRecord implements IRecord {
	CRecord(){
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
}
