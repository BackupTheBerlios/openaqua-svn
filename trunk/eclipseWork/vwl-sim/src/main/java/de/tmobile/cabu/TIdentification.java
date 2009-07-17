/**
 * 
 */
package de.tmobile.cabu;


import java.sql.Timestamp;
import java.util.Set;


/**
 * @author behrenan
 * 
 */

public class TIdentification extends BaseType {

	public static String getPrintHeader(final BaseList list, final String prefix) {
		String result = BaseType.getPrintHeader(list, prefix) + sep();
		result += "CV" + sep();
		result += "ExternalIdentifier" + sep();
		result += "Mandator" + sep();
		result += "ElementTemplateId" + sep();
		result += "ElementMasterTemplateId";
		return result;
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
	public String getPrintString(final Set<Integer> attributList, final String prefix) {
		String result = super.getPrintString(attributList, prefix) + sep();
		result += "\"" + ListIdentification_Cv.getInstances().getTypeAsString(getCv()) + "\"" + sep();
		result += getExternalIdentifier() + sep();
		result += getMandator() + sep();
		result += getElementTemplateId() + sep();
		result += getElementMasterTemplateId() + sep();
		return result;
	}

	public int getType() {
		return type;
	}
}
