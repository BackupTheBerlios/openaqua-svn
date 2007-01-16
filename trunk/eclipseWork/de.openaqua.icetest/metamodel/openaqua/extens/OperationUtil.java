/**
 * 
 */
package openaqua.extens;

import org.openarchitectureware.meta.uml.classifier.Operation;



/**
 * @author behrenan
 *
 */
public class OperationUtil {
	
	/**
	 * @param op - the class which has to be explored
	 * @return returns a string with a complete method signature
	 */

	public static String operationSignature(Operation op) {
		String result = "";
		//Set up the method documenation
		result += "/**\n";
		result += "* UML: " + op.QualifiedName() + "\n";
		result += "*/\n";
		
		result += "/**";
		
		//Is abstract?
		if (op.isAbstract()) result += " abstract ";
		
		//visibility
		if (op.isPrivate()) result += " private ";
		if (op.isPublic()) result += " public ";
		if (op.isProtected()) result += " protected ";
		
		
		//return type
		
		
		//name
		result += op.Name();
		
		//params
		result += "(";
		if (op.hasParameters()) {
			result += "params";
			
		}
		
		result += ")";
		
		//exceptions
		
		
		//bye
		result += "*/";

		return result;
	}
	
} //ClassUtil

