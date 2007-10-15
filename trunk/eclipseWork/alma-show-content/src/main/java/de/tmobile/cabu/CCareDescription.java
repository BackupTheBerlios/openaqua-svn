/**
 * 
 */
package de.tmobile.cabu;



/**
 * @author behrenan
 *
 */
public class CCareDescription extends CBaseType{
	private String description;
	Logger logger = Logger.getRootLogger();

	public CCareDescription (int id, final String description) {
		super(id, 0, null, null);
		this.description = description;
	}
	

	public String getDescription() {
		return this.description;
	}

	public void setDescription(final String description) {
		this.description = description;
	}

	public void print(String prefix) {
		logger.out(prefix+sep()+getId()+sep()+description);
	}

}
