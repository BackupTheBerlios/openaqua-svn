/**
 * 
 */
package de.openaqua.vwl;


import java.sql.Timestamp;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;


/**
 * @author behrenan
 * 
 */
public abstract class BaseType {
	public static String getPrintHeader(final BaseList list, final String prefix) {
		String result = "; ";
		if (prefix != null && prefix.length() > 1) {
			result += "prefix" + sep();
		}
		result += "id" + sep();
		result += "objVers" + sep();
		result += "valid_from" + sep();
		result += "valid_to";
		final Set<Integer> attr = list.getAttributeTypes();
		if (attr != null) {
			for (final Integer integer : attr) {
				result += sep();
				result += ListSubType.getInstances().getTypeAsString(integer);
			}

		}
		return result;
	}

	protected static String makeValue(final String value) {
		if (value == null) {
			return "<NULL>";
		} else {
			return value.trim();
		}
	}

	public static Character sep() {
		return ';';
	}

	private final Map<Integer, String> attributes;
	private final int id;
	private final int obj_version;
	private final Timestamp valid_from;
	private final Timestamp valid_to;

	public BaseType(final int id, final int obj_version, final Timestamp valid_from, final Timestamp valid_to) {
		super();
		this.id = id;
		this.obj_version = obj_version;
		attributes = new TreeMap<Integer, String>();

		if (valid_to == null) {
			this.valid_to = new Timestamp(2145913199000L);
		} else {
			this.valid_to = valid_to;
		}

		if (valid_from == null) {
			this.valid_from = new Timestamp(0L);
		} else {
			this.valid_from = valid_from;
		}
	}

	final public void addAttribute(final BaseList list, final int type, final String value) {
		if (attributes.containsKey(type)) {
			CLogger.getRootLogger().error("Pre Existing Key" + type);
			CLogger.getRootLogger().error("Element = " + getPrintString(null, "BaseElement"));
		}
		attributes.put(type, makeValue(value));
	}

	public int getId() {
		return id;
	}

	public int getObj_version() {
		return obj_version;
	}


	public String getPrintString(final Set<Integer> attributList, final String prefix) {
		String result = "";
		if (prefix != null && prefix.length() > 1) {
			result += prefix;
			result += sep();
		}
		result += id;
		result += sep();
		result += obj_version;
		result += sep();
		result += valid_from.getTime() / 1000;
		result += sep();
		result += valid_to.getTime() / 1000;

		if (attributList != null) {
			for (final Integer integer : attributList) {
				if (attributes.containsKey(integer)) {
					result += sep();
					//result += ListSubType.getInstances().getTypeAsString(integer) + '=';
					result += attributes.get(integer);
				} else {
					result += sep();
					result += "<NULL>";
				}
			}
		}
		return result;
	}

	public final Timestamp getValid_from() {
		return valid_from;
	}


	public final Timestamp getValid_to() {
		return valid_to;
	}

}
