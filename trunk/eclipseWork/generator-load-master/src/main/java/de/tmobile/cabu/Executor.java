/**
 * 
 */
package de.tmobile.cabu;




/**
 * @author behrenan
 *
 */

final public class Executor extends Thread{
	
	/**
	 * Constructor
	 *
	 */
	public Executor() {
		super();
	}
	
	
	
	/**
	 * Might start functions, might do something, what ever
	 */
	public void start() {
		//for (int i = 1; i <= Configuration.getInstance().getThreadCounter(); ++i) {
			//new TTGenerator().start();
		//}
	}


	
	
	/**
	 * The thread execution method
	 */
	public void run () {
		for(;;) {
			yield();
		}
	}

}
