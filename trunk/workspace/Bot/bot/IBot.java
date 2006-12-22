/**
 * 
 */
package bot;

import record.IEvent;

/**
 * @author tukaram
 *
 */
public interface IBot {

	public void registerBot(IBot register);
	public void unregisterBot(IBot register);
	public void inputPort(IEvent event);
	public void outputPort(IEvent event);
}

