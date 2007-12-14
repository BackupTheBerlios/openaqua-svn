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
public abstract class BaseElement extends BaseType {
	public static String getPrintHeader(final String prefix) {
		return BaseType.getPrintHeader(prefix) + sep() + "type" + sep() + "subtype" + sep() + "datatype";
	}

	private final Map<Integer, String> attributes;
	private final BaseListElement list;
	private BaseList ownerList;
	private final int type;
	private final int subtype;
	private final int datatype;
	private final int unittype;
	private final int parentId;
	private final int rootId;
	private final String value;


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
		list = getElementList(id, this);

		try {
			if (list != null) {
				list.refreshList();
			}
		} catch (final SQLException e) {
			CLogger.getRootLogger().error(e.getMessage());
			e.printStackTrace();
		}

	}

	final public void addAttribute(final BaseList list, final int type, final String value) {
		list.storeAttributeType(type);
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

	abstract protected BaseListElement getElementList(final int id, final BaseElement parent);

	public int getParentId() {
		return parentId;
	}


	private String getPrintString(final BaseList list, final String prefix) {
		//do nothing if empty
		//if (list.size() <= 0) { return ""; }
		String result = super.getPrintPrefixString(prefix + " \"" + ListElementType.getInstances().getTypeAsString(type) + "\"") + sep();
		result += sep() + ":" + sep();
		result += "root=" + rootId + sep();
		result += "parent=" + parentId + sep();
		result += " type=" + type + " sub=" + subtype;
		result += sep() + "#" + sep();
		result += printAttributes(list);
		result += sep() + "#" + sep();
		return result;
	}

	@Override
	public String getPrintString(final String prefix) {
		return getPrintString(ownerList, prefix);
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

	private String printAttributes(final BaseList list) {
		String result = "";
		for (final Integer i : list.getAttributeTypes()) {
			if (attributes.containsKey(i)) {
				result += attributes.get(i) + sep();
			} else {
				result += "<NULL>" + sep();
			}
		}

		return result;

	}

	public void setOwnerList(final BaseList list) {
		ownerList = list;
	}


}
