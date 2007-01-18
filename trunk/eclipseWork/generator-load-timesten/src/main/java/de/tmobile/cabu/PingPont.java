/**
 * 
 */
package de.tmobile.cabu;

/**
 * @author behrenan
 *
 */
public class PingPont extends Thread {

	private String word; // What word to print  
	private int delay; // how long to pause  
	public PingPont(String whatToSay, int delayTime) { 
		word = whatToSay;  
		delay = delayTime;  
	} 
	
	
	public void run() { 
		try { 
			for (;;) { 
				System.out.print(word + " ");  
				sleep(delay); // wait until next time  
			} 
		} catch (InterruptedException e) { 
			return; // end this thread;  
		} 
	} 
} 

