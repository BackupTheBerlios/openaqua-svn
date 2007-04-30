/**
 * 
 */
package de.openaqua.dev.cartridges.asn.helper;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
//import org.andromda.metafacades.emf.uml2.ClassifierFacadeLogicImpl;


/**
 * @author behrenan
 *
 */
public class AsnHelper {
	
	final public String currentDateTime;
	public AsnHelper() {
		super();
		Calendar cal = Calendar.getInstance(); 
		DateFormat formater = new SimpleDateFormat(); 
		currentDateTime = formater.format(cal.getTime());
		//org.andromda.metafacades.emf.uml2.ClassifierFacadeLogicImpl foo;
	}
	
	
	/**
	 * @return the currentDateTime
	 */
	public String getCurrentDateTime() {
		return this.currentDateTime;
	}
	

}
