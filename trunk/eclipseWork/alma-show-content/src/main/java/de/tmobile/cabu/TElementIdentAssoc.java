/**
 * 
 */
package de.tmobile.cabu;


import java.sql.Timestamp;


/**
 * @author behrenan
 * 
 */
public class TElementIdentAssoc extends BaseType {

	public static String getPrintHeader(final String prefix) {
		return BaseType.getPrintHeader(prefix) + sep() + "elementId";
	}

	long elementId;

	public TElementIdentAssoc(final int id, final long elementId, final int obj_version, final Timestamp valid_from, final Timestamp valid_to) {
		super(id, obj_version, valid_from, valid_to);
		this.elementId = elementId;
		/*
		 * if (obj_version != 1) { final Integer i = new Integer(id);
		 * Logger.getRootLogger().error("obj version != 1 for id=" +
		 * i.toString()); }
		 */
	}

	/**
	 * @return the elementId
	 */
	public long getElementId() {
		return elementId;
	}

	@Override
	public String getPrintString(final String prefix) {
		return super.getPrintPrefixString(prefix) + sep() + elementId;
	}

	/**
	 * @param elementId
	 *           the elementId to set
	 */
	public void setElementId(final long elementId) {
		this.elementId = elementId;
	}

}
