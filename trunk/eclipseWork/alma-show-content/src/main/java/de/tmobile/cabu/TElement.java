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
public class TElement extends BaseElement {
	private final int templId;
	private final int templVers;
	private final Timestamp insertTime;

	public TElement(final int id, final int type, final int subtype, final int datatype, final int unittype, final int parentId,
			final int rootId, final String value, final Timestamp insertTime, final int templId, final int templVers) {

		super(id, 1, null, null, type, subtype, datatype, unittype, parentId, rootId, value);
		this.templId = templId;
		this.templVers = templVers;
		this.insertTime = insertTime;

	}


	@Override
	protected BaseListElement getElementList(final int id, final BaseElement parent) {
		return null;
		//return new ListElementPart(id, parent);
	}


	@Override
	protected List<Integer> getKnownAttributes(final int elementType) {
		return CKnownElementAttributes.getInstances().getKnownElementAttributes(elementType);
	}

	@Override
	public String getPrintString(final String prefix) {
		return super.getPrintString(prefix);
		/*
		final String result = super.getPrintString(prefix);
		result += templId + sep();
		result += templVers + sep();
		result += insertTime;
		return result;
		*/
	}

	@Override
	public void storeAttributeType(final int typeAttribute) {
		CKnownElementAttributes.getInstances().setKnownElementAttributes(getType(), typeAttribute);
	}


}
