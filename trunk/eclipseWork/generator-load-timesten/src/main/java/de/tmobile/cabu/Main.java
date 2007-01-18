/**
 * 
 */
package de.tmobile.cabu;

import java.sql.SQLException;




/**
 * @author behrenan
 *
 */
public class Main {

	
	/**
	 * setup a database structure
	 * @return true if fine
	 */
	private static boolean setupDatabase(){

		try {
			TTConnection con;
			con = new TTConnection("com.timesten.jdbc.TimesTenDriver", "jdbc:timesten:direct:RunData_tt51");
			con.Connect();
			con.CreateTableStructure();
			con.Disconnect();
			return true;
		} catch (ClassNotFoundException e1) {
			System.err.println("Java ClassNotFound: " + e1.getMessage());
			//e1.printStackTrace();
		} catch (SQLException e) {
			System.err.println("SQLException: " + e.getMessage());
			e.printStackTrace();
		}
		return false;
	}
		
	
	
	
	/**
	 * makes the measuring
	 * @throws ClassNotFoundException 
	 *
	 */
	private static void execution () throws ClassNotFoundException {		
        
        //setup threads
        TTGenerator[] threadArray = new TTGenerator[Configuration.getInstance().getMaxConnections()];
        for (int i = 0; i < Configuration.getInstance().getMaxConnections(); i++) {
        	threadArray[i] = new TTGenerator( "" + i );
        	threadArray[i].Init();
        }
        

        //fire up all threads
        Stats.getInstance().setGlobalTime(System.nanoTime());
        for (int i = 0; i < Configuration.getInstance().getMaxConnections(); i++) {
        	threadArray[i].start();
        }
        
        //wait for finish
        for (int i = 0; i < Configuration.getInstance().getMaxConnections(); i++) {
        	try {
				threadArray[i].join();
			} catch (InterruptedException e) {
				System.err.println("Error while joining a thread");
				e.printStackTrace();
			}
    		//System.out.println( "Finished Generator Run with Connection ID " + getName());
        }
        long diff = System.nanoTime()-Stats.getInstance().getGlobalTime();
        
        //print stat infos
        double ms = diff/1000000; //yepp, durch 10000. Oder???
        double msP = ms/Configuration.getInstance().getMaxConnections();
        System.out.println( "Finished Load Test in " + ms +" ms = " + msP + " ms/Connection ");

	}
	
	
	/**
	 * @param args
	 * @throws InterruptedException 
	 */
	public static void main(String[] args) throws InterruptedException {
        System.out.println( "Start Load Test" );
        long runTime = 0;
        
        
        //setup Database
        if (setupDatabase() != true) {
        	System.err.println("Finish after Error");
        	
        } else {
        	
        	//and does the measuring stuff
        	try {
        		long start = System.currentTimeMillis();
				execution();
				runTime = System.currentTimeMillis() - start;
			} catch (ClassNotFoundException e) {
				System.err.println( "Run was aborted by an exception");
				e.printStackTrace();
			}
        }
        
        //Stats
        Stats.getInstance().printResults();
        System.out.println( "Runtime was " +runTime + "ms");
        
        
	}

}
