/**
 * 
 */
package de.tmobile.cabu;



/**
 * @author behrenan
 *
 */
public class CSubType extends CCareDescription{
	public CSubType(int id, String description) {
		super(id, description);
		String desc = description.replaceFirst("CABU[- ]", "");
		desc = desc.replaceFirst("Attribut[e]?", "");
		setDescription(desc);
	}
}
