/**
 * 
 */
package de.tmobile.cabu;


import java.sql.Timestamp;


/**
 * @author behrenan
 * 
 */
public class TElementTmpl extends BaseElement {
	public static String getPrintHeader(final String prefix) {
		return BaseType.getPrintHeader(prefix) + sep() + "type" + sep() + "subtype" + sep() + "datatype";
	}

	private final int masterTemplId;
	private final int masterTemplVers;
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

	/**
	 * @return the acmDescId
	 */
	public int getAcmDescId() {
		return acmDescId;
	}

	/**
	 * @return the constFlag
	 */
	public int getConstFlag() {
		return constFlag;
	}

	/* (non-Javadoc)
	 * @see de.tmobile.cabu.BaseElement#getElementList(int, de.tmobile.cabu.BaseElement)
	 */
	@Override
	protected BaseListElement getElementList(final int id, final BaseElement parent) {
		return new ListElementTmplPart(id, parent);
	}

	/**
	 * @return the masterTemplId
	 */
	public int getMasterTemplId() {
		return masterTemplId;
	}

	/**
	 * @return the masterTemplVers
	 */
	public int getMasterTemplVers() {
		return masterTemplVers;
	}


	@Override
	public String getPrintString(final String prefix) {
		return "";
		//do nothing if empty
		//if (list.size() <= 0) { return ""; }

		//String result = super.getPrintPrefixString(prefix + " \"" + ListElementType.getInstances().getTypeAsString(type) + "\"") + sep();
		//result += rootId + sep();
		//result += parentId + sep();
		//result += type + sep();
		//result += subtype + sep();
		//result += "\"" + CElementSubtypeList.getInstances().getTypeAsString(subtype) + "\"" + sep();
		//result += "\"" + CDataTypeList.getInstances().getTypeAsString(datatype) + "\"" + sep();
		//result += "\"" + value + "\"" + sep();
		//result += printAttributes();
		//return result;
		//list.printElements(prefix);
	}


}
