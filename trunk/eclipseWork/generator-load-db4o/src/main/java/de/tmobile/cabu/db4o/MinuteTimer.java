/**
 * 
 */
package de.tmobile.cabu.db4o;

import java.util.TimerTask;
import java.text.*; 
import de.tmobile.cabu.loadtest.Stats;

/**
 * @author behrenan
 *
 */
final public class MinuteTimer extends TimerTask{
	DateFormat shortTime = DateFormat.getTimeInstance(); ;
	int msec;
	public MinuteTimer(int msec) {
		this.msec = msec;
	}

	public void run (){
		Stats.getInstance().printResults(msec);
	}

}
