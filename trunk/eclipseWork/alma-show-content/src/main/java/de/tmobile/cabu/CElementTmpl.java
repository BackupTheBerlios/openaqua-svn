/**
 * 
 */
package de.tmobile.cabu;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;



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


	public void refresh(TTConnection connection) throws SQLException {
		if (!connection.isConnected()) return;

		// exec SQL command
		Statement stmt = connection.createStatement();
		ResultSet rs = stmt
				.executeQuery("select value, element_subtype_cv, root_id, obj_version, parent_id, valid_from, valid_to from acm_schema.acm$ta_element_tmpl where element_template_id=" + id());

		// parse the result
		while (rs.next()) {
			if (rs.getString(1) != null)	value = rs.getString(1).trim();
			subType = CSubTypeList.getInstances().get(rs.getInt(2));
			rootId = rs.getInt(3);
			objVersion = rs.getInt(4);
			parentId = rs.getInt(5);
			validFrom = rs.getDate(6).toString() +  " " + rs.getTime(6).toString();
			validTo = rs.getDate(7).toString() +  " " + rs.getTime(7).toString();
			
		}

		// close statements
		rs.close();
		stmt.close();
	}

	public void setValue(final String value) {
		this.value=value;
	}
	
	public String getPrintLine(final String prefix) {
		String result = "";
		result += prefix		+ sep();
		result += getId() 		+ sep();
		result += getRootId()	+ sep();
		result += getParentId() + sep();
		return result;
	}
	
	
	@Override
	public void print(final String prefix) {
		System.out.println(getPrintLine(prefix));
	}
	
	

	public Integer id() {
		return id;
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
