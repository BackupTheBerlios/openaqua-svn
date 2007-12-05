/**
 * 
 */
package de.tmobile.cabu;


import java.sql.Timestamp;
import java.util.Map;
import java.util.TreeMap;


/**
 * @author behrenan
 * 
 */
public class CElementTmpl extends CBaseType {
	public static String getPrintHeader(final String prefix) {
		return CBaseType.getPrintHeader(prefix) + sep() + "type" + sep() + "subtype" + sep() + "datatype";
	}

	public final Map<Integer, String> attributes;
	private int type;
	private int subtype;
	private int datatype;
	private int unittype;
	private int parentId;
	private int rootId;
	private int amcDescId;
	private int constFlag;
	private String value;
	private final CElementTmplPartList list;

	public CElementTmpl(final int id, final int obj_version, final Timestamp valid_from, final Timestamp valid_to, final int type,
			final int subtype, final int datatype, final int unittype, final int parentId, final int rootId, final int amcDescId,
			final int constFlag, final String value) {
		super(id, obj_version, valid_from, valid_to);
		this.type = type;
		this.subtype = subtype;
		this.datatype = datatype;
		this.unittype = unittype;
		this.parentId = parentId;
		this.rootId = rootId;
		this.amcDescId = amcDescId;
		this.constFlag = constFlag;
		if (value == null) {
			this.value = "";
		} else {
			this.value = value.trim();
		}
		attributes = new TreeMap<Integer, String>();

		list = new CElementTmplPartList(id);
		list.run();

	}

	/**
	 * @return the amcDescId
	 */
	public int getAmcDescId() {
		return amcDescId;
	}

	/**
	 * @return the constFlag
	 */
	public int getConstFlag() {
		return constFlag;
	}

	/**
	 * @return the datatype
	 */
	public int getDatatype() {
		return datatype;
	}

	/**
	 * @return the parentId
	 */
	public int getParentId() {
		return parentId;
	}

	/**
	 * @return the rootId
	 */
	public int getRootId() {
		return rootId;
	}

	/**
	 * @return the subtype
	 */
	public int getSubtype() {
		return subtype;
	}

	/**
	 * @return the type
	 */
	public int getType() {
		return type;
	}

	/**
	 * @return the unittype
	 */
	public int getUnittype() {
		return unittype;
	}

	/**
	 * @return the value
	 */
	public String getValue() {
		return value;
	}

	/* (non-Javadoc)
	 * @see de.tmobile.cabu.CBaseType#print(java.lang.String)
	 */
	@Override
	public void print(final String prefix) {
		String result = super.getPrintString(prefix) + sep();
		result += rootId + sep();
		result += type + sep();
		result += "\"" + CElementTypeList.getInstances().getTypeAsString(type) + "\"" + sep();
		result += "\"" + CElementSubtypeList.getInstances().getTypeAsString(subtype) + "\"" + sep();
		//result += "\"" + CDataTypeList.getInstances().getTypeAsString(datatype) + "\"" + sep();
		result += "\"" + value + "\"" + sep();
		Logger.getRootLogger().out(result);
		list.printElements("   " + prefix);
	}

	/**
	 * @param amcDescId
	 *           the amcDescId to set
	 */
	public void setAmcDescId(final int amcDescId) {
		this.amcDescId = amcDescId;
	}

	/**
	 * @param constFlag
	 *           the constFlag to set
	 */
	public void setConstFlag(final int constFlag) {
		this.constFlag = constFlag;
	}

	/**
	 * @param datatype
	 *           the datatype to set
	 */
	public void setDatatype(final int datatype) {
		this.datatype = datatype;
	}

	/**
	 * @param parentId
	 *           the parentId to set
	 */
	public void setParentId(final int parentId) {
		this.parentId = parentId;
	}

	/**
	 * @param rootId
	 *           the rootId to set
	 */
	public void setRootId(final int rootId) {
		this.rootId = rootId;
	}

	/**
	 * @param subtype
	 *           the subtype to set
	 */
	public void setSubtype(final int subtype) {
		this.subtype = subtype;
	}

	/**
	 * @param type
	 *           the type to set
	 */
	public void setType(final int type) {
		this.type = type;
	}

	/**
	 * @param unittype
	 *           the unittype to set
	 */
	public void setUnittype(final int unittype) {
		this.unittype = unittype;
	}

	/**
	 * @param value
	 *           the value to set
	 */
	public void setValue(final String value) {
		this.value = value;
	}


}
