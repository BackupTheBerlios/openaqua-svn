/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */

public class CIdentification extends CListableObject{
	private int IDENTIFICATION_ID;
	private int IDENTIFICATION_TY;
	private int IDENTIFICATION_CV;
	private int MANDATOR_ID;
	private int ELEMENT_TEMPLATE_ID;
	private int ELEMENT_MASTER_TEMPLATE_ID;
	private String EXTERNAL_IDENTIFIER;
	private int OBJ_VERSION;
	private String VALID_FROM;
	private String VALID_TO;
	private Logger logger = Logger.getRootLogger();

	public CIdentification() {
		super();
	}

	public int getELEMENT_MASTER_TEMPLATE_ID() {
		return this.ELEMENT_MASTER_TEMPLATE_ID;
	}

	public void setELEMENT_MASTER_TEMPLATE_ID(int element_master_template_id) {
		this.ELEMENT_MASTER_TEMPLATE_ID = element_master_template_id;
	}

	public int getELEMENT_TEMPLATE_ID() {
		return this.ELEMENT_TEMPLATE_ID;
	}

	public void setELEMENT_TEMPLATE_ID(int element_template_id) {
		this.ELEMENT_TEMPLATE_ID = element_template_id;
	}

	public String getEXTERNAL_IDENTIFIER() {
		return this.EXTERNAL_IDENTIFIER;
	}

	public void setEXTERNAL_IDENTIFIER(String external_identifier) {
		if (external_identifier != null) {
			this.EXTERNAL_IDENTIFIER = external_identifier.trim();
		} else {
			this.EXTERNAL_IDENTIFIER = null;
		}
	}

	public int getIDENTIFICATION_CV() {
		return this.IDENTIFICATION_CV;
	}

	public void setIDENTIFICATION_CV(int identification_cv) {
		this.IDENTIFICATION_CV = identification_cv;
	}

	public int getIDENTIFICATION_ID() {
		return this.IDENTIFICATION_ID;
	}

	public void setIDENTIFICATION_ID(int identification_id) {
		this.IDENTIFICATION_ID = identification_id;
	}

	public int getIDENTIFICATION_TY() {
		return this.IDENTIFICATION_TY;
	}

	public void setIDENTIFICATION_TY(int identification_ty) {
		this.IDENTIFICATION_TY = identification_ty;
	}

	public int getMANDATOR_ID() {
		return this.MANDATOR_ID;
	}

	public void setMANDATOR_ID(int mandator_id) {
		this.MANDATOR_ID = mandator_id;
	}

	public int getOBJ_VERSION() {
		return this.OBJ_VERSION;
	}

	public void setOBJ_VERSION(int obj_version) {
		this.OBJ_VERSION = obj_version;
	}

	public String getVALID_FROM() {
		return this.VALID_FROM;
	}

	public void setVALID_FROM(String valid_from) {
		this.VALID_FROM = valid_from;
	}

	public void setVALID_FROM(String date, String time) {
		String result = "";
		if (date != null) result += date;
		if (time != null) {
			if (result != null) result += " ";
			result += time;
		}
		this.VALID_FROM=result;
	}
	
	public String getVALID_TO() {
		return this.VALID_TO;
	}

	public void setVALID_TO(String date, String time) {
		String result = "";
		if (date != null) result += date;
		if (time != null) {
			if (result != null) result += " ";
			result += time;
		}
		this.VALID_TO=result;
	}

	public void setVALID_TO(String valid_to) {
		this.VALID_TO = valid_to;
	}


	@Override
	public void print(String prefix) {
		String result = "";
		result += getIDENTIFICATION_ID()+sep(); //Database ID
		result += getOBJ_VERSION()+sep();
		result += getMANDATOR_ID()+sep();
		result += getEXTERNAL_IDENTIFIER()+sep(); //MSISDN oder Vertrag
		result += "\""+CDescriptionList.getInstances().get(getIDENTIFICATION_TY()).getDescription()+"\""+sep();; //Type of Element
		result += "\""+CDescriptionList.getInstances().get(getIDENTIFICATION_CV()).getDescription()+"\""+sep();; //Description
		result += getVALID_FROM()+sep();
		result += getVALID_TO();
		logger.info(result);
	}

}
