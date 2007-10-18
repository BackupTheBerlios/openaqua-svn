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
	private int type;
	private int cv;
	private int mandator;
	private int elementTemplateId;
	private int elementMasterTemplateId;
	private String externalIdentifier;

	final private Logger logger = Logger.getRootLogger();

	public CIdentification(
			int id, 		int obj_version,	Timestamp valid_from,		Timestamp valid_to, 
			int type, 		int cv, 			int mandator,				int elementTemplateId, 
			int elementMasterTemplateId,		String externalIdentifier) {
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
		return this.cv;
	}

	public int getElementMasterTemplateId() {
		return this.elementMasterTemplateId;
	}

	public int getElementTemplateId() {
		return this.elementTemplateId;
	}

	public String getExternalIdentifier() {
		return this.externalIdentifier;
	}

	public int getMandator() {
		return this.mandator;
	}

	public int getType() {
		return this.type;
	}

	public void print(String prefix) {
		String result = super.getPrintString(prefix) + sep();
		/*
		result += "\""
				+ CDescriptionList.getInstances().get(new Integer(getType()))
						.getDescription() + "\"" + sep();
		result += "\""
				+ CDescriptionList.getInstances().get(new Integer(getCv()))
						.getDescription() + "\"" + sep();

		*/
		logger.out(result);
	}

}
