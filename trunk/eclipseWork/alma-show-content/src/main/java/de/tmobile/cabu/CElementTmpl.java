/**
 * 
 */
package de.tmobile.cabu;


import java.sql.SQLException;
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

	private final Map<Integer, String> attributes;
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

		list = new CElementTmplPartList(id, this);
		try {
			list.refreshList();
		} catch (final SQLException e) {
			Logger.getRootLogger().error(e.getMessage());
			e.printStackTrace();
		}

	}

	public void addAttribute(final int type, final String value) {
		KnownElementAttributes.getInstances().setKnownTemplateAttributes(this.type, type);
		if (value != null) {
			attributes.put(type, value.trim());
		}
	}

	public int getAmcDescId() {
		return amcDescId;
	}

	public int getConstFlag() {
		return constFlag;
	}

	public int getDatatype() {
		return datatype;
	}

	public int getParentId() {
		return parentId;
	}

	@Override
	public String getPrintString(final String prefix) {
		//do nothing if empty
		if (list.size() <= 0) { return ""; }

		String result = super.getPrintPrefixString(prefix + " \"" + CElementTypeList.getInstances().getTypeAsString(type) + "\"") + sep();
		result += rootId + sep();
		result += parentId + sep();
		//result += type + sep();
		//result += subtype + sep();
		//result += "\"" + CElementSubtypeList.getInstances().getTypeAsString(subtype) + "\"" + sep();
		//result += "\"" + CDataTypeList.getInstances().getTypeAsString(datatype) + "\"" + sep();
		//result += "\"" + value + "\"" + sep();
		result += printAttributes();
		return result;
		//list.printElements(prefix);
	}

	public int getRootId() {
		return rootId;
	}

	public int getSubtype() {
		return subtype;
	}

	public int getType() {
		return type;
	}

	public int getUnittype() {
		return unittype;
	}

	public String getValue() {
		return value;
	}

	public void listAttribute() {
	//final String result = "TEMPLATE"
	}

	public void prepareForPrinting() {
		final UnifiedTableOutput output = new UnifiedTableOutput();


	}

	private String printAttributes() {
		String result = "";
		for (final Integer i : KnownElementAttributes.getInstances().getKnownTemplateAttributes(getType())) {
			if (attributes.containsKey(i)) {
				result += attributes.get(i) + sep();
				//result += i + "=" + "\"" + attributes.get(i) + "\"" + sep();
			} else {
				result += sep();
				//result += i + "=" + "\"\"" + sep();
			}
		}
		return result;

	}

	public void setAmcDescId(final int amcDescId) {
		this.amcDescId = amcDescId;
	}

	public void setConstFlag(final int constFlag) {
		this.constFlag = constFlag;
	}

	public void setDatatype(final int datatype) {
		this.datatype = datatype;
	}

	public void setParentId(final int parentId) {
		this.parentId = parentId;
	}

	public void setRootId(final int rootId) {
		this.rootId = rootId;
	}

	public void setSubtype(final int subtype) {
		this.subtype = subtype;
	}

	public void setType(final int type) {
		this.type = type;
	}

	public void setUnittype(final int unittype) {
		this.unittype = unittype;
	}

	public void setValue(final String value) {
		this.value = value;
	}


}
