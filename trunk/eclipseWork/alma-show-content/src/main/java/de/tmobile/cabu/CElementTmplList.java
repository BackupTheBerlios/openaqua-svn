/**
 * 
 */
package de.tmobile.cabu;




/**
 * @author behrenan
 * 
 */
public class CElementTmplList extends CElementTmplPartList {
	private static CElementTmplList INSTANCE = new CElementTmplList(0);

	public static CElementTmplList getInstances() {
		return INSTANCE;
	}

	/**
	 * @param parentId
	 */
	public CElementTmplList(final int parentId) {
		super(parentId);
	}


	/* (non-Javadoc)
	 * @see de.tmobile.cabu.CBaseList#getQueryString()
	 */
	//@Override
	//protected String getQueryString() {
	//	return "select element_template_id, element_type_cv, element_subtype_cv, data_type_cv, unit_cv, parent_id, "
	//			+ " root_id, acm_description_id, const_flag, value, obj_version, valid_from, valid_to from acm_schema.acm$ta_element_tmpl where parent_id is null";
	//}
}
