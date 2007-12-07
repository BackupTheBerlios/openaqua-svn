/**
 * 
 */
package de.tmobile.cabu;




/**
 * @author behrenan
 * 
 */

public class TParentId extends BaseType {

	public static String getPrintHeader(final String prefix) {
		return prefix + sep() + "parentId";
	}


	public TParentId(final int id) {
		super(id, 0, null, null);
	}


	@Override
	public String getPrintString(final String prefix) {
		final String result = prefix + sep() + getId();
		return result;
	}
}
