/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class CCareDescription extends CBaseType {

	public static String getPrintHeader(final String prefix) {
		String result = "prefix" + sep() + sep() + sep();
		result += "id" + sep();
		result += "description";
		return result;
	}

	private String description;

	public CCareDescription(final int id, final String description) {
		super(id, 0, null, null);
		this.description = description;
	}

	public String getDescription() {
		return description;
	}

	@Override
	public String getPrintString(final String prefix) {
		return prefix + sep() + getId() + sep() + description;
	}

	public void setDescription(final String description) {
		this.description = description;
	}

}
