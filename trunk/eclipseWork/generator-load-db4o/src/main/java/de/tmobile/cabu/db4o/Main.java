/**
 * 
 */
package de.tmobile.cabu.db4o;

import java.io.File;

import com.db4o.Db4o;
import com.db4o.ObjectContainer;

/**
 * @author tukaram
 *
 */
public class Main {
	final static String filename = "Foo.dat";

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		DbTestClass test = new DbTestClass();
		File f = new File( filename );
		if (f.exists()) f.delete();

		ObjectContainer database;

		System.out.println("===============Simple Store==============");
		database = Db4o.openFile(filename);
		test.simpleStore(database);
		test.dumpDatabase(database);
		database.close();

		database = Db4o.openFile(filename);
		//test.simpleLoad(database);
		test.dumpDatabase(database);
		database.close();
	
		System.out.println("===============Simple Update=============");
		database = Db4o.openFile(filename);
		test.simpleUpdate(database);
		database.close();

		database = Db4o.openFile(filename);
		test.dumpDatabase(database);
		database.close();

	}

}
