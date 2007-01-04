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
	final int commandId;
	
	public CRunnableCommand (final int commandId, IContext context) {
		this.commandId = commandId; 
		this.context = context;
	}
	
	public void run() {
		ICommand command = CFactoryCommands.getInstance().getCommand(commandId);
		command.execute(context);		
	}
	
	public final int getCommandId() {
		return commandId;
	}
}
