/**
 * 
 */
package openaqua.base;

/**
 * @author tukaram
 *
 */
public interface IEvent {

	/**
	 * Makes a deep copy of a record
	 * @return
	 */
	public IEvent clone();

	/**
	 * Resets all internal data to an "empty" default state. That state might be different than
	 * the state which a record has after creation by a prototype factory
	 *
	 */
	public void reset();
	
	//public int hashCode();

	/**
	 * Compares two objects and compares all internal values.<br>
	 * 
	 * The method must be overidden. Otherwise the default behaviour happes which
	 * simply compares the object reference.
	 * 
	 * @see {@link http://www.javaworld.com/javaqa/2002-06/01-qa-0621-hashtable.html} for
	 * detailed description about overriding.
	 * @param object the object which has to be compared
	 * @return true = the object are equal
	 */
	public boolean equals(java.lang.Object object);

}
