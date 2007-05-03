/**
 * 
 */
package de.openaqua.dev.cartridges.asn.helper;

import java.util.Collection;
import java.util.Date;
import java.util.Iterator;

import org.apache.log4j.Logger;



/**
 * @author behrenan
 *
 */
public class AsnHelper {
	final private Logger logger = Logger.getRootLogger();

	public AsnHelper() {
		super();
		//org.andromda.metafacades.emf.uml2.ClassifierFacadeLogicImpl foo;
		logger.warn("Construct AsnHelper");
		
	}
	
	
	/**
	 * @return the currentDateTime
	 */
	public String getCurrentDateTime() {
		return new Date().toString();
	}

	
	public String whatObject(final String c, final Object o){
		logger.error(c+"whatObject o="+o.toString());
		return "";
	}

	public String listACollection(Collection c){
		String result = "listACollection";
		if (c.isEmpty()){
			logger.error("Collection is empty");
			return result;
		} else {
			Iterator it = c.iterator();
			while(it.hasNext()){
				Object o = it.next();
				logger.warn("c has Object "+o.toString());
			}
		}
		
		return result;
	}

}
