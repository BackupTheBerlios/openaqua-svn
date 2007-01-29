/**
 * 
 */
package de.tmobile.cabu.db4o;

/**
 * @author behrenan
 *
 */
public class EDatabaseInUse  extends RuntimeException {
	/**
	 * 
	 */
	private static final long serialVersionUID = -3334471378658248874L;

	EDatabaseInUse () {
		super();
	}

	public EDatabaseInUse( String s ) { 
		super( s ); 
	} 

}
