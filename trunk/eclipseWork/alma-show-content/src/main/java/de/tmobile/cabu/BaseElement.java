/**
 * 
 */
package de.tmobile.cabu;


import java.sql.SQLException;
import java.sql.Timestamp;
import java.util.List;
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
			list.refreshList();
		} catch (final SQLException e) {
			CLogger.getRootLogger().error(e.getMessage());
			e.printStackTrace();
		}

	}

	final public void addAttribute(final int type, final String value) {
		storeAttributeType(type);
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

	abstract protected List<Integer> getKnownAttributes(final int elementType);

	public int getParentId() {
		return parentId;
	}

	@Override
	public String getPrintString(final String prefix) {
		//do nothing if empty
		//if (list.size() <= 0) { return ""; }
		String result = super.getPrintPrefixString(prefix + " \"" + ListElementType.getInstances().getTypeAsString(type) + "\"") + sep();
		result += rootId + sep();
		result += parentId + sep();
		result += printAttributes();
		return result;
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
		for (final Integer i : getKnownAttributes(getType())) {
			if (attributes.containsKey(i)) {
				result += attributes.get(i) + sep();
			} else {
				result += "<NULL>" + sep();
			}
		}
		return result;

	}


	abstract public void storeAttributeType(final int typeAttribute);


}
