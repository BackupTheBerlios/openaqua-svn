/**
 * 
 */
package de.tmobile.cabu;


import java.sql.Timestamp;


/**
 * @author behrenan
 * 
 */
public abstract class BaseType {
	public static String getPrintHeader(final String prefix) {
		String result = "prefix" + sep();
		result += "id" + sep();
		result += "objVers" + sep();
		result += "valid_from" + sep();
		result += "valid_to" + sep();
		return result;
	}

	public static Character sep() {
		return ',';
	}

	private int id;
	private int obj_version;
	private Timestamp valid_from;
	private Timestamp valid_to;

	public BaseType(final int id, final int obj_version, final Timestamp valid_from, final Timestamp valid_to) {
		super();
		this.id = id;
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

	public int getObj_version() {
		return obj_version;
	}

	public String getPrintString(final String prefix) {
		String result = prefix + sep();
		result += id;
		result += sep();
		result += obj_version;
		result += sep();
		result += valid_from.getTime() / 1000;
		result += sep();
		result += valid_to.getTime() / 1000;
		return result;
	}

	public final Timestamp getValid_from() {
		return valid_from;
	}


	public final Timestamp getValid_to() {
		return valid_to;
	}


	/**
	 * @param id
	 *           the id to set
	 */
	public void setId(final int id) {
		this.id = id;
	}

	/**
	 * @param obj_version
	 *           the obj_version to set
	 */
	public void setObj_version(final int obj_version) {
		this.obj_version = obj_version;
	}

	/**
	 * @param valid_from
	 *           the valid_from to set
	 */
	public void setValid_from(final Timestamp valid_from) {
		this.valid_from = valid_from;
	}

	/**
	 * @param valid_to
	 *           the valid_to to set
	 */
	public void setValid_to(final Timestamp valid_to) {
		this.valid_to = valid_to;
	}

}
