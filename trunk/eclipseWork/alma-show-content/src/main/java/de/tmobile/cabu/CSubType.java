/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 *
 */
public class CSubType {
	private Integer id;
	private String description;
//	private Logger logger = Logger.getRootLogger();
	
	public CSubType() {
		this.id = 0;
		this.description = "";
	}
	
	public CSubType(Integer id, String description) {
		this.id = id;
		this.description = description;
	}

	/**
	 * @return the id
	 */
	public Integer getId() {
		return this.id;
	}

	/**
	 * @param id the id to set
	 */
	public void setId(Integer id) {
		this.id = id;
	}

	/**
	 * @return the value
	 */
	public String getDescription() {
		return this.description;
	}

	/**
	 * @param value the value to set
	 */
	public void setValue(String description) {
		this.description = description;
	}
	
	public void list() {
		System.out.println(id+"\t"+description);
		
	}

}
