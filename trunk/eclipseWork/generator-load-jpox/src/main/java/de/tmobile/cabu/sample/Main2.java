/**
 * 
 */
package de.tmobile.cabu.sample;

import java.io.File;

import org.apache.log4j.ConsoleAppender;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.apache.log4j.PatternLayout;
import com.db4o.Db4o;
import com.db4o.ObjectContainer;
import de.tmobile.cabu.db4o.DatabaseServerRegistry;
import de.tmobile.cabu.db4o.ServerConfiguration;

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
			
			Db4o.configure().messageLevel(0);
			//System.out.println("===============Simple Store==============");			
			//ObjectServer s = Db4o.openServer("foo2.dat", 10000);
			//ObjectServer s = Db4o.openServer("foo2.dat", 0);
			//s.grantAccess("a", "b");
			//ObjectContainer d = Db4o.openClient("localhost", 10000, "a", "b");
			//ObjectContainer d = s.openClient();
			//d.close();
			//s.close();
			//System.out.println("===============Simple Store==============");			
			//if (1==1) return;
			


			File f = new File( filename );
			if (f.exists()) f.delete();
			ServerConfiguration conf = new ServerConfiguration(filename, 10000, "localhost");
			final String username = "test";
			final String password = "test";
			conf.addUser(username, password);
			DatabaseServerRegistry.getInstance().registerServer(key, conf);


			ObjectContainer database;

			System.out.println("===============Simple Store==============");
			database = DatabaseServerRegistry.getInstance().getClient(key, username, password);
			test.simpleStore(database);
			test.dumpDatabase(database);
			database.close();


			System.out.println("===============Simple Update=============");
			database = DatabaseServerRegistry.getInstance().getClient(key, username, password);
			test.simpleUpdateContract(database);
			test.simpleUpdateContractContainer(database);
			test.dumpDatabase(database);
			database.close();

			System.out.println("===============Lookup and Update=============");
			database = DatabaseServerRegistry.getInstance().getClient(key, username, password);
			test.simpleLookupAndUpdate(database);
			database.close();

			System.out.println("===============Final Dump=============");
			database = DatabaseServerRegistry.getInstance().getClient(key, username, password);
			test.dumpDatabase(database);
			database.close();

			
			DatabaseServerRegistry.getInstance().stopAndRemoveAllServers();
			System.out.println("===============Finish=============");
			
			
		}catch (Exception e) {
			System.err.print(e.getLocalizedMessage());
			e.printStackTrace();			
		}

	}

}
