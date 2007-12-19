/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class TDescription extends BaseType {

	public static String getPrintHeader(final String prefix) {
		String result = "prefix" + sep() + sep() + sep();
		result += "id" + sep();
		result += "description";
		return result;
	}

	private String description;

	public TDescription(final int id, final String description) {
		super(id, 0, null, null);
		this.description = description;
	}

	public String getDescription() {
		return description;
	}

	@Override
	public String getPrintString(final String prefix) {
		String result = prefix;
		result += sep();
		result += getId();
		result += sep();
		result += description;
		return result;
	}

	public void setDescription(final String description) {
		this.description = description;
	}

}
