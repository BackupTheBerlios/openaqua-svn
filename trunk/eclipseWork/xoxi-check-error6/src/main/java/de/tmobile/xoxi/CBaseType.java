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
	private int id;
	private Integer id2;
	private int obj_version;
	private Timestamp valid_from;
	private Timestamp valid_to;

	public CBaseType(int id, int obj_version, Timestamp valid_from, Timestamp valid_to) {
		super();
		this.id = id;
		this.id2 = new Integer(id);
		this.obj_version = obj_version;
		this.valid_from = valid_from;
		this.valid_to = valid_to;
	}

	public int getId() {
		return id;
	}

	public Integer getIntegerId() {
		return id2;
	}

	public int getObj_version() {
		return this.obj_version;
	}

	public String getValid_from() {
		if (this.valid_from == null) return null;
		return this.valid_from.toString();
	}

	public String getValid_to() {
		if (this.valid_to == null) return null;
		return this.valid_to.toString();
	}

	public String getPrintString(final String prefix) {
		String result = prefix + sep();
		result += id + sep();
		result += obj_version + sep();
		result += valid_from + sep();
		result += valid_to;
		return result;
	}

	abstract public void print(String prefix);

}
