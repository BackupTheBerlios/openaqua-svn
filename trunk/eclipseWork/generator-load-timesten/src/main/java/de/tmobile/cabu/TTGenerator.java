/**
 * 
 */
package de.tmobile.cabu;

/**
 * @author behrenan
 *
 */
public class TTGenerator extends Thread{
	
	private int done = 0;
	private int maxContracts = Configuration.getInstance().getMaxContracts();
	
	/**
	 * Constructor
	 */
	public TTGenerator(ThreadGroup group, String threadName) {
		super( group, threadName); 
	}

	/**
	 * Constructor without threadgroup
	 */
	public TTGenerator(String threadName) {
		super( threadName); 
		System.out.println( "Start new TTGenerator Thread" );
	}




	private void execute() {
		done++;
		//System.out.println( "Runde: " + done + "from thread "+getName());
	    //for ( int i = 0; i < 20; i++ )  System.out.println( new java.util.Date() );  
	}


	
	/**
	 * The thread execution method
	 * runs endless
	 */
	public void run () {
		try {
			while (done < maxContracts) {
				execute();
				//yield();
				sleep(100);
			}
		//} catch (InterruptedException e) {
		} catch (Exception e) {
			System.out.println( "Murks");
			e.printStackTrace();
			return;
		}
	}
}
