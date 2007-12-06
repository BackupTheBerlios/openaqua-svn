/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class ListElement extends ListElementPart {
	private static final long serialVersionUID = -8580341561632406783L;
	private static ListElement INSTANCE = new ListElement(0);

	public static ListElement getInstances() {
		return INSTANCE;
	}

	public ListElement(final int parentId) {
		super(parentId, null);
	}

}
