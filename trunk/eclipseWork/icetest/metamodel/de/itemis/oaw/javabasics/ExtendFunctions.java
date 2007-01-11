/*
   Copyright 2006 by    
   
       itemis GmbH & Co. KG
       Heinrichstr. 51
       D-44536 Luenen
       Germany
       http://www.itemis.de

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
package de.itemis.oaw.javabasics;

import java.util.HashMap;
import java.util.Map;

import org.openarchitectureware.meta.uml.Type;
import org.openarchitectureware.meta.uml.classifier.Class;
import org.openarchitectureware.meta.uml.classifier.PrimitiveType;

public class ExtendFunctions {
	private static Map<String, String> defaultReturns;
	private static final String[] TYPE_PACKAGES = {"java.lang", "java.util"};
	
	static {
		defaultReturns = new HashMap<String, String>();
		defaultReturns.put("int", "-1");
		defaultReturns.put("long", "-1");
		defaultReturns.put("short", "-1");
		defaultReturns.put("byte", "-1");
		defaultReturns.put("boolean", "false");
		defaultReturns.put("char", "''");
	}
	
	public static String getSerialVersionUid (Class pClass) {
		int result = pClass.Id().hashCode();
		try {
			int version = Integer.parseInt(Configuration.getVersion());
			// XOR the hashCode with the version
			result ^= version;
		} catch (Exception ignored) {
			; // do nothing
		}
		return Integer.toString(result);
	}

	public static String getDefaultReturn (Type pType) {
		String lDefaultReturn = (String) defaultReturns.get(pType.NameS());
		return lDefaultReturn!=null ? lDefaultReturn : "null";
	}
	
	public static String fqn (PrimitiveType pType) {
		for (int i=0; i<TYPE_PACKAGES.length; i++) {
			try {
				String fqn = TYPE_PACKAGES[i]+"."+pType.NameS();
				java.lang.Class.forName(fqn);
				return fqn; // no exception => Class found
			} catch (Exception ignore) {
				;
			}
		}
		// no match
		return pType.NameS();
	}
}
