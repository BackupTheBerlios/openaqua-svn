/**
 * 
 */
package de.tmobile.cabu;

import java.sql.Timestamp;



/**
 * @author behrenan
 *
 */
public class CAssoc  extends CBaseType {
	private long element_id;
	Logger logger = Logger.getRootLogger();
	
	public CAssoc(int id, int obj_version, Timestamp valid_from, Timestamp valid_to, long element_id) {
		super(id, obj_version, valid_from, valid_to);
		this.element_id = element_id;
	}
	
	public long getElement_id() {
		return this.element_id;
	}

	public void print(String prefix) {
		String result = super.getPrintString(prefix) + sep() + element_id;
		logger.out(result);
		
	}
	
	

}
