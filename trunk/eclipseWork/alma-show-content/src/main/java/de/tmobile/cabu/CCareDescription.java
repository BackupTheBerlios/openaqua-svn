/**
 * 
 */
package de.tmobile.cabu;

/**
 * @author behrenan
 *
 */
public class CCareDescription extends CListableObject{
	private Integer id;
	private String description;
	Logger logger = Logger.getRootLogger();
	
	private CCareDescription () {super();}
	
	public CCareDescription (Integer id, String description) {
		this.id = id;
		this.description = description;
	}

	public String getDescription() {
		return this.description;
	}


	public Integer getId() {
		return this.id;
	}

	public Integer getDescId() {
		return this.id;
	}

	
	public void print(String prefix) {
		logger.info(prefix+sep()+id+sep()+description);
	}
	
}
