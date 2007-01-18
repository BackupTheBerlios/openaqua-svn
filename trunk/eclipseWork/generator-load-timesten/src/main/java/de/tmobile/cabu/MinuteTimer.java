/**
 * 
 */
package de.tmobile.cabu;

import java.util.TimerTask;
/**
 * @author behrenan
 *
 */
final public class MinuteTimer extends TimerTask{
	

	public void run (){
		Stats.getInstance().printResults();
	   
	}

}
