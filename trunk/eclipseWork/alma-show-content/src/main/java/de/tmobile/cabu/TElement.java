/**
 * 
 */
package de.tmobile.cabu;


import java.sql.Timestamp;


/**
 * @author behrenan
 * 
 */
public class TElement extends BaseElement {
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

}
