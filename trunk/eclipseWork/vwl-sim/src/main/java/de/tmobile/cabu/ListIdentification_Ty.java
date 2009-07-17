/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class ListIdentification_Ty extends BaseListAlmaDataType {
	private static final long serialVersionUID = 1056598853660288336L;
	private static ListIdentification_Ty INSTANCE = new ListIdentification_Ty();

	public static ListIdentification_Ty getInstances() {
		return INSTANCE;
	}

	@Override
	protected String getQueryString() {
		return "select identification_ty, description_id, sorting, valid from acm_schema.acm$ta_identification_ty ";
	}

}
