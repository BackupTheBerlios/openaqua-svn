/**
 * 
 */
package de.tmobile.cabu;

import java.sql.Timestamp;

/**
 * @author behrenan
 * 
 */

public class CIdentification extends CBaseType {
	public static String getPrintHeader(final String prefix) {
		return CBaseType.getPrintHeader(prefix) + sep() + "type" + sep() + "cv";
	}

	private final int type;
	private final int cv;
	private final int mandator;
	private final int elementTemplateId;
	private final int elementMasterTemplateId;

	private String externalIdentifier;

	final private Logger logger = Logger.getRootLogger();

	public CIdentification(final int id, final int obj_version, final Timestamp valid_from, final Timestamp valid_to, final int type,
			final int cv, final int mandator, final int elementTemplateId, final int elementMasterTemplateId, final String externalIdentifier) {
		super(id, obj_version, valid_from, valid_to);
		this.type = type;
		this.cv = cv;
		this.mandator = mandator;
		this.elementTemplateId = elementTemplateId;
		this.elementMasterTemplateId = elementMasterTemplateId;
		this.externalIdentifier = externalIdentifier;
		if (this.externalIdentifier != null) {
			this.externalIdentifier = externalIdentifier.trim();
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

	public int getType() {
		return type;
	}

	@Override
	public void print(final String prefix) {
		String result = super.getPrintString(prefix) + sep();
		result += getType() + sep();
		result += getCv() + sep();
		/*
		 * result += "\"" + CDescriptionList.getInstances().get(new
		 * Integer(getType())) .getDescription() + "\"" + sep(); result += "\"" +
		 * CDescriptionList.getInstances().get(new Integer(getCv()))
		 * .getDescription() + "\"" + sep();
		 * 
		 */
		logger.out(result);
	}

}
