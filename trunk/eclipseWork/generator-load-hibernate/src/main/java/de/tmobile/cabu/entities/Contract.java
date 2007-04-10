/**
 * 
 */
package de.tmobile.cabu.entities;

import javax.persistence.Entity;
import javax.persistence.Table;



/**
 * 
 *
 */
@Entity
@Table(name = "contract")
public class Contract {

	private long id;
	private int value;
	private String stringValue;
	private String name;

	public Contract() {
		super();
	}

	public Contract(final int value) {
		super();
		this.value = new Integer(value);
	}

	
	
	public Contract(final String stringValue, final int value) {
		super();
		this.stringValue = stringValue;
		this.value = new Integer(value);
	}

	





	/**
	 * @return the value
	 */
	public Integer getValue() {
		return value;
	}


	/**
	 * @param value the value to set
	 */
	public void setValue(int value) {
		this.value = value;
		this.stringValue = "value("+value+")";
	}

	public void dump() {
		//System.out.println("   Contract("+contractKey.getKey()+")\tvalue="+value);
		//contractKey.dump();
	}


	public String getStringValue() {
		return stringValue;
	}



	/**
	 * @return the name
	 */
	public final String getName() {
		return name;
	}



	/**
	 * @param name the name to set
	 */
	public final void setName(String name) {
		this.name = name;
	}



	/**
	 * @return the id
	 */
	public long getId() {
		return this.id;
	}



	/**
	 * @param id the id to set
	 */
	public void setId(long id) {
		this.id = id;
	}



	/**
	 * @param stringValue the stringValue to set
	 */
	public void setStringValue(String stringValue) {
		this.stringValue = stringValue;
	}



	/**
	 * @param value the value to set
	 */
	public void setValue(Integer value) {
		this.value = value;
	}





}
