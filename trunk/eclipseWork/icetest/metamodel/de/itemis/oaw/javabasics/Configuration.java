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

import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Properties;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.tools.ant.util.FileUtils;
import org.openarchitectureware.workflow.util.ResourceLoader;
import org.openarchitectureware.workflow.util.ResourceLoaderFactory;

public class Configuration {
	private static final Log LOG = LogFactory.getLog(Configuration.class);
	private static final String PREFIX = Configuration.class.getPackage().getName();
	public static final String CFG_PACKAGEPREFIX = PREFIX+".packagePrefix";
	public static final String CFG_VERSION = PREFIX+".version";
	public static final String CFG_FILEHEADERDOC = PREFIX+".fileHeaderDoc";
	
	private static Properties props = new Properties();
	static {
		try {
			InputStream is = Thread.currentThread().getContextClassLoader().getResourceAsStream(PREFIX+".properties");
			if (is!=null) 
				props.load(is); 
			else 
				LOG.warn("Property file '"+PREFIX+".properties' not found in classpath.");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}

	public static String getPackagePrefix () {
		String prefix = props.getProperty(CFG_PACKAGEPREFIX);
		return prefix!=null ? prefix.trim()+"." : "";
	}
	
	public static String getVersion () {
		String result = props.getProperty(CFG_VERSION);
		return result!=null ? result.trim() : null;
	}
	
	public static String getFileHeaderDoc () {
		String result = "";
		String fileHeader = props.getProperty(CFG_FILEHEADERDOC);
		if (fileHeader!=null) {
			try {
				ResourceLoader rl = ResourceLoaderFactory.createResourceLoader();
				InputStream is = rl.getResourceAsStream(fileHeader);
				if (is!=null) {
					result = FileUtils.readFully(new InputStreamReader(is));
				} else {
					LOG.warn("Could not locate File Header Doc file '"+fileHeader+"'");
				}
			} catch (IOException exc) {
				LOG.warn("Could not read File Header Doc file '"+fileHeader+"': "+exc.getMessage());
			}
		} 
		return result;
	}
}
