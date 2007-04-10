/**
 *
 */
package de.openaqua.regTestHelper;

import java.util.TimerTask;
import java.text.*;

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
		RegTestStats.getInstance().printResults(msec);
		//System.out.println(shortTime.format(new Date()));

	}
}
