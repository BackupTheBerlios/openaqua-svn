/**
 * 
 */
package de.tmobile.cabu;

/**
 * @author behrenan
 *
 */
public class CAttribute {
	Integer elementId;
	Integer elementType;
	CSubType elementSubtype;
	String value;
	
	public CAttribute() {
		
	}
	
	public CAttribute(	Integer elementId,	Integer elementType,CSubType elementSubtype,String value) {
		this.elementId=elementId;
		this.elementType=elementType;
		this.elementSubtype=elementSubtype;
		this.value=value;
	}

	/**
	 * @return the elementId
	 */
	public Integer getElementId() {
		return this.elementId;
	}
	/**
	 * @param elementId the elementId to set
	 */
	public void setElementId(Integer elementId) {
		this.elementId = elementId;
	}
	/**
	 * @return the elementSubtype
	 */
	public CSubType getElementSubtype() {
		return this.elementSubtype;
	}
	/**
	 * @param elementSubtype the elementSubtype to set
	 */
	public void setElementSubtype(CSubType elementSubtype) {
		this.elementSubtype = elementSubtype;
	}
	/**
	 * @return the elementType
	 */
	public Integer getElementType() {
		return this.elementType;
	}
	/**
	 * @param elementType the elementType to set
	 */
	public void setElementType(Integer elementType) {
		this.elementType = elementType;
	}
	/**
	 * @return the value
	 */
	public String getValue() {
		return this.value;
	}
	/**
	 * @param value the value to set
	 */
	public void setValue(String value) {
		this.value = value;
	}

}
