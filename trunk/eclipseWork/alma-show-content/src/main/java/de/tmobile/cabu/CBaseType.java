/**
 * 
 */
package de.tmobile.cabu;

import java.sql.Timestamp;

/**
 * @author behrenan
 * 
 */
public abstract class CBaseType extends CListableObject {
	public static String getPrintHeader(final String prefix) {
		String result = "prefix" + sep() + sep() + sep();
		result += "id" + sep();
		result += "objVersion" + sep();
		result += "valid_from" + sep();
		result += "valid_to" + sep();
		return result;
	}

	private final int id;
	private final Integer id2;
	private final int obj_version;
	private Timestamp valid_from;
	private Timestamp valid_to;

	public CBaseType(final int id, final int obj_version, final Timestamp valid_from, final Timestamp valid_to) {
		super();
		this.id = id;
		id2 = new Integer(id);
		this.obj_version = obj_version;
		this.valid_from = valid_from;
		this.valid_to = valid_to;

		if (this.valid_to == null) {
			this.valid_to = new Timestamp(2145913199000L);
		}

		if (this.valid_from == null) {
			this.valid_from = new Timestamp(0L);
		}
	}

	public int getId() {
		return id;
	}

	public Integer getIntegerId() {
		return id2;
	}

	public int getObj_version() {
		return obj_version;
	}

	public String getPrintString(final String prefix) {
		String result = prefix + sep();
		result += id + sep();
		result += obj_version + sep();
		result += valid_from + sep();
		result += valid_to;
		return result;
	}

	public String getValid_from() {
		if (valid_from == null) { return null; }
		return valid_from.toString();
	}

	public String getValid_to() {
		if (valid_to == null) { return null; }
		return valid_to.toString();
	}

	@Override
	abstract public void print(String prefix);

}
