/**
 * 
 */
package de.tmobile.cabu;


import java.sql.Timestamp;


/**
 * @author behrenan
 * 
 */

public class TIdentification extends BaseType {

	public static String getPrintHeader(final String prefix) {
		return BaseType.getPrintHeader(prefix) + "type" + sep() + sep() + "value" + sep() + sep() + "mandator" + sep() + "tmplId" + sep()
				+ "masterTemplId";
	}

	private final int type;
	private final int cv;
	private final int mandator;
	private final int elementTemplateId;
	private final int elementMasterTemplateId;
	private final String externalIdentifier;

	public TIdentification(final int id, final int obj_version, final Timestamp valid_from, final Timestamp valid_to, final int type,
			final int cv, final int mandator, final int elementTemplateId, final int elementMasterTemplateId, final String externalIdentifier) {
		super(id, obj_version, valid_from, valid_to);
		this.type = type;
		this.cv = cv;
		this.mandator = mandator;
		this.elementTemplateId = elementTemplateId;
		this.elementMasterTemplateId = elementMasterTemplateId;
		if (externalIdentifier != null) {
			this.externalIdentifier = externalIdentifier.trim();
		} else {
			this.externalIdentifier = null;
		}

	}

	public int getCv() {
		return cv;
	}

	public int getElementMasterTemplateId() {
		return elementMasterTemplateId;
	}

	public int getElementTemplateId() {
		return elementTemplateId;
	}

	public String getExternalIdentifier() {
		return externalIdentifier;
	}

	public int getMandator() {
		return mandator;
	}

	@Override
	public String getPrintString(final String prefix) {
		String result = super.getPrintPrefixString(prefix) + sep();
		//result += "\"" + getType() + "=\"" + sep();
		//result += "\"" + ListIdentification_Ty.getInstances().getTypeAsString(getType()) + "\"" + sep();
		result += "\"" + ListIdentification_Cv.getInstances().getTypeAsString(getCv()) + "\"" + sep();
		result += getExternalIdentifier() + sep();
		result += getMandator() + sep();
		result += getElementTemplateId() + sep();
		result += getElementMasterTemplateId();
		return result;
	}

	public int getType() {
		return type;
	}
}
