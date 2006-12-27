/**
 * 
 */
package openaqua.base;

/**
 * @author tukaram
 *
 */
public interface IRecord {

	/**
	 * Makes a deep copy of a record
	 * @return
	 */
	public IRecord clone();

	/**
	 * Resets all internal data to an "empty" default state. That state might be different than
	 * the state which a record has after creation by a prototype factory
	 *
	 */
	public void reset();
}
