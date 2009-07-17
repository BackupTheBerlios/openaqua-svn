/**
 * 
 */
package de.tmobile.cabu;


import java.sql.Timestamp;
import java.util.Set;


/**
 * @author behrenan
 * 
 */
public class TElement extends BaseElement {
	public static String getPrintHeader(final BaseList list, final String prefix) {
		String result = BaseElement.getPrintHeader(list, prefix) + sep();
		result += "TemplateId" + sep();
		result += "TemplateVersion" + sep();
		result += "InsertionTime";
		return result;
	}
	public final int templId;
	public final int templVers;

	public final Timestamp insertTime;

	public TElement(final int id, final int type, final int subtype, final int datatype, final int unittype, final int parentId,
			final int rootId, final String value, final Timestamp insertTime, final int templId, final int templVers) {

		super(id, 1, null, null, type, subtype, datatype, unittype, parentId, rootId, value);
		this.templId = templId;
		this.templVers = templVers;
		this.insertTime = insertTime;

	}


	@Override
	public String getPrintString(final Set<Integer> attributList, final String prefix) {
		String result = super.getPrintString(attributList, prefix);
		result += templId;
		result += sep();
		result += templVers;
		result += sep();
		result += insertTime.getTime() / 1000;
		return result;
	}

}
