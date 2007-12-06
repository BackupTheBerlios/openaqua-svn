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
public class BaseElement extends BaseType {
	public static String getPrintHeader(final String prefix) {
		return BaseType.getPrintHeader(prefix) + sep() + "type" + sep() + "subtype" + sep() + "datatype";
	}

	private final Map<Integer, String> attributes;
	private final ListElementTmplPart list;

	private int type;
	private int subtype;
	private int datatype;
	private int unittype;
	private int parentId;
	private int rootId;
	private String value;


	public BaseElement(final int id, final int obj_version, final Timestamp valid_from, final Timestamp valid_to, final int type,
			final int subtype, final int datatype, final int unittype, final int parentId, final int rootId, final String value) {

		super(id, obj_version, valid_from, valid_to);
		this.type = type;
		this.subtype = subtype;
		this.datatype = datatype;
		this.unittype = unittype;
		this.parentId = parentId;
		this.rootId = rootId;

		if (value == null) {
			this.value = "";
		} else {
			this.value = value.trim();
		}

		attributes = new TreeMap<Integer, String>();
		list = new ListElementTmplPart(id, this);

		try {
			list.refreshList();
		} catch (final SQLException e) {
			CLogger.getRootLogger().error(e.getMessage());
			e.printStackTrace();
		}

	}

	public void addAttribute(final int type, final String value) {
		CKnownElementAttributes.getInstances().setKnownTemplateAttributes(this.type, type);
		if (value != null) {
			attributes.put(type, value.trim());
		}
	}

	public void buildUnifiedPrintList(final String prefix, final CUnifiedTableOutput uto) {
		if (attributes.size() > 0) {
			uto.add(getType(), getPrintString(prefix));
			for (final BaseType base : list.values()) {
				((BaseElement) base).buildUnifiedPrintList(prefix, uto);
			}
		}
	}

	public int getDatatype() {
		return datatype;
	}

	public int getParentId() {
		return parentId;
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


	private String printAttributes() {
		String result = "";
		for (final Integer i : CKnownElementAttributes.getInstances().getKnownTemplateAttributes(getType())) {
			if (attributes.containsKey(i)) {
				result += attributes.get(i) + sep();
			} else {
				result += "<NULL>" + sep();
			}
		}
		return result;

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
