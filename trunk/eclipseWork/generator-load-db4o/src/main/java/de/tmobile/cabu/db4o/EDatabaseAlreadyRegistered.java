/**
 * 
 */
package de.tmobile.cabu.db4o;

/**
 * @author behrenan
 *
 */
public class EDatabaseAlreadyRegistered extends RuntimeException {
	private static final long serialVersionUID = 6616428412307084211L;
	/**
	 * 
	 */

	EDatabaseAlreadyRegistered () {
		super();
	}

	public EDatabaseAlreadyRegistered( String s ) { 
		super( s ); 
	} 

}
