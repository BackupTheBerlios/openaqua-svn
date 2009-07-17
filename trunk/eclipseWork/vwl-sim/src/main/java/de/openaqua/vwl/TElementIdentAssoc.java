/**
 * 
 */
package de.openaqua.vwl;


import java.sql.Timestamp;
import java.util.Set;


/**
 * @author behrenan
 * 
 */
public class TElementIdentAssoc extends BaseType {

	public static String getPrintHeader(final BaseList list, final String prefix) {
		return BaseType.getPrintHeader(list, prefix) + sep() + "elementId";
	}

	long elementId;

	public TElementIdentAssoc(final int id, final long elementId, final int obj_version, final Timestamp valid_from, final Timestamp valid_to) {
		super(id, obj_version, valid_from, valid_to);
		this.elementId = elementId;
	}

	/**
	 * @return the elementId
	 */
	public long getElementId() {
		return elementId;
	}

	@Override
	public String getPrintString(final Set<Integer> attributList, final String prefix) {
		String result = super.getPrintString(attributList, prefix);
		result += sep();
		result += elementId;
		return result;
	}

	/**
	 * @param elementId
	 *           the elementId to set
	 */
	public void setElementId(final long elementId) {
		this.elementId = elementId;
	}

}
