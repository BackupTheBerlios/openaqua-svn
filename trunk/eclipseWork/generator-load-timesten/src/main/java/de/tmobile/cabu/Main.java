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

	private static boolean setupDatabase(){
		TTConnection  con= new TTConnection("com.timesten.jdbc.TimesTenDriver", "jdbc:timesten:direct:RunData_tt51");
		try {
			con.CreateTableStructure();
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		}
		con.Disconnect();
		return true;
	}
	
	
	private static void execution () {
		
        
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
        
        //nothing more to do. Systems waits upuntil all threads are finished

        //wait for finishing
        //Stats.getInstance().setGlobalTime(System.nanoTime());
        //while(ttGroup.activeCount()==0);
		//long diff = System.nanoTime()-Stats.getInstance().getGlobalTime();
        
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
        long start = System.currentTimeMillis();
        //setup Database
        if (setupDatabase() != true) {
        	System.err.println("Finish after Error");
        } else {
        	execution();
        }
        long runTime = System.currentTimeMillis() - start;
        System.out.println( "Runtime was " +runTime + "ms");
        
        
	}

}
