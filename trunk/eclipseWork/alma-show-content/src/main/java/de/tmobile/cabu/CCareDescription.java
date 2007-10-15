/**
 * 
 */
package de.tmobile.cabu;

import java.sql.Timestamp;

/**
 * @author behrenan
 *
 */
public class CCareDescription extends CBaseType{
	private String description;
	Logger logger = Logger.getRootLogger();

	public CCareDescription (int id, int obj_version, Timestamp valid_from, Timestamp valid_to, final String description) {
		super(id, obj_version, valid_from, valid_to);
		this.description = description;
	}
	

	public String getDescription() {
		return this.description;
	}


	public void print(String prefix) {
		logger.info(prefix+sep()+getId()+sep()+description);
	}
	
}
