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
	public static String getPrintHeader(final String prefix) {
		return BaseType.getPrintHeader(prefix) + sep() + "type" + sep() + "subtype" + sep() + "datatype";
	}

	private final Timestamp insertTime;
	private final int templId;
	private final int templVers;

	public TElement(final int id, final int obj_version, final Timestamp valid_from, final Timestamp valid_to, final int type,
			final int subtype, final int datatype, final int unittype, final int parentId, final int rootId, final String value,
			final Timestamp insertTime, final int templId, final int templVers) {

		super(id, obj_version, valid_from, valid_to, type, subtype, datatype, unittype, parentId, rootId, value);
		this.insertTime = insertTime;
		this.templId = templId;
		this.templVers = templVers;

	}


	/**
	 * @return the insertTime
	 */
	public Timestamp getInsertTime() {
		return insertTime;
	}


	@Override
	public String getPrintString(final String prefix) {
		return "";
		//do nothing if empty
		//if (list.size() <= 0) { return ""; }

		//String result = super.getPrintPrefixString(prefix + " \"" + CElementTypeList.getInstances().getTypeAsString(type) + "\"") + sep();
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


	/**
	 * @return the templId
	 */
	public int getTemplId() {
		return templId;
	}


	/**
	 * @return the templVers
	 */
	public int getTemplVers() {
		return templVers;
	}


}
