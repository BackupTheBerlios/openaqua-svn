/**
 * 
 */
package openaqua.base;


/**
 * @author behrenan
 *
 */
final public class CRunnableCommand implements Runnable {
	final IContext context;
	final ICommand command;
	
	public CRunnableCommand (ICommand command, IContext context) {
		this.command = command; 
		this.context = context;
	}
	
	public void run() {
		command.execute(context);		
	}
}
