/**
 * 
 */
package de.tmobile.cabu;


import java.sql.Timestamp;
import java.util.List;


/**
 * @author behrenan
 * 
 */
public class TElementTmpl extends BaseElement {
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
	protected BaseListElement getElementList(final int id, final BaseElement parent) {
		return new ListElementTmplPart(id, parent);
	}


	@Override
	protected List<Integer> getKnownAttributes(final int elementType) {
		return CKnownElementAttributes.getInstances().getKnownTemplateAttributes(elementType);
	}


	@Override
	public String getPrintString(final String prefix) {
		String result = super.getPrintString(prefix);
		result += acmDescId + sep();
		result += constFlag + sep();
		return result;
	}

	@Override
	public void storeAttributeType(final int typeAttribute) {
		CKnownElementAttributes.getInstances().setKnownTemplateAttributes(getType(), typeAttribute);
	}

}
