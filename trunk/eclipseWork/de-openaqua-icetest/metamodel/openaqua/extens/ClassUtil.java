/**
 * 
 */
package openaqua.extens;

import org.openarchitectureware.meta.uml.classifier.Class;
import org.openarchitectureware.meta.uml.classifier.Package;


/**
 * @author behrenan
 *
 */
public class ClassUtil {
	
	/**
	 * @param cls - the class which has to be explored
	 * @return returns a string with the correct package name for a java class
	 */
	public static String getPackageName (Class cls) {
		String result = "";
		
		for (Package pck=cls.Package(); pck!=null;	pck=pck.SuperPackage()) {
			result = pck.NameS() + (result.length()>0 ?	"."+result : "");
		}
		return result;
	}
} //ClassUtil

