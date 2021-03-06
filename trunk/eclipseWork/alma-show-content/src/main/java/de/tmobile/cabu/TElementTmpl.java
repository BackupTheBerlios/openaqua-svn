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
public class TElementTmpl extends BaseElement {
	public static String getPrintHeader(final BaseList list, final String prefix) {
		String result = BaseElement.getPrintHeader(list, prefix) + sep();
		result += "acmDescId" + sep();
		result += "constFlag" + sep();
		result += "MasterTemplateId" + sep();
		result += "MasterTemplVersion";
		return result;
	}
	public final int masterTemplId;
	public final int masterTemplVers;
	private final int acmDescId;

	private final int constFlag;


	public TElementTmpl(final int id, final int obj_version, final Timestamp valid_from, final Timestamp valid_to, final int type,
			final int subtype, final int datatype, final int unittype, final int parentId, final int rootId, final int acmDescId,
			final int constFlag, final String value, final int masterTemplId, final int masterTemplVers) {

		super(id, obj_version, valid_from, valid_to, type, subtype, datatype, unittype, parentId, rootId, value);
		this.acmDescId = acmDescId;
		this.constFlag = constFlag;
		this.masterTemplId = masterTemplId;
		this.masterTemplVers = masterTemplVers;
	}


	@Override
	public String getPrintString(final Set<Integer> attributList, final String prefix) {
		String result = super.getPrintString(attributList, prefix);
		result += acmDescId;
		result += sep();
		result += constFlag;
		result += sep();
		return result;
	}


}
