/**
 * 
 */
package de.tmobile.cabu;


import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;


/**
 * @author behrenan
 * 
 */
public class ListElementTmplPart extends BaseListElement {
	private static final long serialVersionUID = 1774619855321319700L;


	public ListElementTmplPart(final int parentId, final BaseElement parent) {
		super(parentId, parent);
	}


	@Override
	protected String getQueryString() {
		if (getParentId() == 0) {
			return "select element_template_id, element_type_cv, element_subtype_cv, data_type_cv, unit_cv, parent_id, "
					+ " root_id, acm_description_id, const_flag, value, obj_version, valid_from, valid_to, elem_mstr_tmpl_id, elem_mstr_tmpl_vers "
					+ " from acm_schema.acm$ta_element_tmpl where parent_id is null and parent_id is null order by element_template_id";

		} else {
			final String result = "select element_template_id, element_type_cv, element_subtype_cv, data_type_cv, unit_cv, parent_id, "
					+ " root_id, acm_description_id, const_flag, value, obj_version, valid_from, valid_to, elem_mstr_tmpl_id, elem_mstr_tmpl_vers "
					+ " from acm_schema.acm$ta_element_tmpl where parent_id=" + getParentId() + " order by element_template_id";
			return result;
		}
	}


	@Override
	protected void HandleQueryResult(final ResultSet rs) throws SQLException {
		while (rs.next()) {
			final int id = rs.getInt(1);
			final int type = rs.getInt(2);
			final int subtype = rs.getInt(3);
			final int datatype = rs.getInt(4);
			final int unittype = rs.getInt(5);
			final int pareId = rs.getInt(6);
			final int rootId = rs.getInt(7);
			final int amcDescId = rs.getInt(8);
			final int constFlag = rs.getInt(9);
			final String value = rs.getString(10);
			final int objVers = rs.getInt(11);
			final Timestamp valid_from = rs.getTimestamp(12);
			final Timestamp valid_to = rs.getTimestamp(13);
			final int tmplMasterId = rs.getInt(14);
			final int tmplMasterVers = rs.getInt(15);


			final TElementTmpl tmpl = new TElementTmpl(id, objVers, valid_from, valid_to, type, subtype, datatype, unittype, pareId, rootId,
					amcDescId, constFlag, value, tmplMasterId, tmplMasterVers);

			store(tmpl);

			if (getParent() != null) {
				getParent().addAttribute(subtype, value);
			}


		}
	}
}
