/**
 * 
 */
package de.tmobile.cabu;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Set;

/**
 * @author behrenan
 *
 */
public class CElementTmpl extends CListableObject{
	private Integer id;
	private Integer tmplVersion;
	private Integer typeCv;
	private Integer objVersion;
	private CSubType subType;
	private Integer dataType;
	private Integer unitCv;
	private Integer parentId;
	private Integer rootId;
	private String	value;
	private String validFrom;
	private String validTo;

	private CElementTmpl() {
		id = 0;
	}

	public CElementTmpl(Integer id) {
		super();
		this.id =id;
	}

	/* (non-Javadoc)
	 * @see de.tmobile.cabu.IElement#list()
	 */
	public void list(String type, Integer spaces) {
		String result = spaces(spaces)+id;
		if (subType != null) result = result + " " + subType.getDescription();
		result = result + " = " + value;
		System.out.println(result);
	}

	public Integer id() {
		return id;
	}

	public void refresh(TTConnection connection) throws SQLException {
		if (!connection.isConnected()) return;

		// exec SQL command
		Statement stmt = connection.createStatement();
		ResultSet rs = stmt
				.executeQuery("select value, element_subtype_cv, root_id, obj_version, parent_id, valid_from, valid_to from acm_schema.acm$ta_element_tmpl where element_template_id=" + id());

		// parse the result
		while (rs.next()) {
			value = rs.getString(1);
			subType = CSubTypeList.getInstances().get(rs.getInt(2));
			rootId = rs.getInt(3);
			objVersion = rs.getInt(4);
			parentId = rs.getInt(5);
			//validFrom = rs.getTime(6).toGMTString();
			//validTo = rs.getTime(7).toLocaleString();
		}

		// close statements
		rs.close();
		stmt.close();
	}

	public void collectElementTmplSubTypes(Set<Integer> ids) {
		if (subType != null && value != null) {
			ids.add(subType.getId());
		}
	}
	
	public void setValue(final String value) {
		this.value = value;
	}
	
	public void listFormated(Set<Integer> attributeTypes, String line) {
		if (subType == null) return;
		if (!attributeTypes.contains(subType.getId())) return;
		line=value+sep();
	}

	/**
	 * @return the dataType
	 */
	public Integer getDataType() {
		return this.dataType;
	}

	/**
	 * @return the id
	 */
	public Integer getId() {
		return this.id;
	}

	/**
	 * @return the parentId
	 */
	public Integer getParentId() {
		return this.parentId;
	}

	/**
	 * @return the rootId
	 */
	public Integer getRootId() {
		return this.rootId;
	}

	/**
	 * @return the subType
	 */
	public CSubType getSubType() {
		return this.subType;
	}

	/**
	 * @return the tmplVersion
	 */
	public Integer getTmplVersion() {
		return this.tmplVersion;
	}

	/**
	 * @return the typeCv
	 */
	public Integer getTypeCv() {
		return this.typeCv;
	}

	/**
	 * @return the unitCv
	 */
	public Integer getUnitCv() {
		return this.unitCv;
	}

	/**
	 * @return the validFrom
	 */
	public String getValidFrom() {
		return this.validFrom;
	}

	/**
	 * @return the validTo
	 */
	public String getValidTo() {
		return this.validTo;
	}

	/**
	 * @return the value
	 */
	public String getValue() {
		return this.value;
	}

	/**
	 * @return the objVersion
	 */
	public Integer getObjVersion() {
		return this.objVersion;
	}
	
}
