/**
 * 
 */
package de.tmobile.cabu.db4o;

import java.io.File;

import org.apache.log4j.ConsoleAppender;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.apache.log4j.PatternLayout;

import com.db4o.Db4o;
import com.db4o.ObjectContainer;

/**
 * @author tukaram
 *
 */
public class Main2 {
	final private static String filename = "Foo.dat";
	final private static String key = "testcase";
	final private static Logger logger = Logger.getRootLogger();


	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			PatternLayout layout = new PatternLayout( "%-5p [%t] %C{1} -> %m%n" );
			ConsoleAppender consoleAppender = new ConsoleAppender( layout );
			logger.addAppender( consoleAppender );
			logger.setLevel( Level.ALL);

			DbTestClass test = new DbTestClass();


			File f = new File( filename );
			if (f.exists()) f.delete();
			Db4oDatabaseRegistry.getInstance().registerDatabasefile(key, filename);


			Db4o.configure().messageLevel(0);
			ObjectContainer database;

			System.out.println("===============Simple Store==============");
			database = Db4oDatabaseRegistry.getInstance().getClient(key);
			test.simpleStore(database);
			test.dumpDatabase(database);
			database.close();

			if(1==2) {
				database = Db4oDatabaseRegistry.getInstance().getClient(key);
				test.simpleLoad(database);
				test.dumpDatabase(database);
				database.close();
			}

			System.out.println("===============Simple Update=============");
			database = Db4oDatabaseRegistry.getInstance().getClient(key);
			test.simpleUpdateContract(database);
			test.simpleUpdateContractContainer(database);
			test.dumpDatabase(database);
			database.close();

			database = Db4oDatabaseRegistry.getInstance().getClient(key);
			test.dumpDatabase(database);
			database.close();
		}catch (Exception e) {
			System.err.print(e.getLocalizedMessage());
			e.printStackTrace();			
		}

	}

}
