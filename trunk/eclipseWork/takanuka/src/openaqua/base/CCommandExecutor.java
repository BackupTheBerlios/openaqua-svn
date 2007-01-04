package openaqua.base;


final public class CCommandExecutor implements Runnable  {
	private ICommand command;
	private IEvent event;

	public CCommandExecutor() {
		super();
	}
	
	
	public void run() {
		command.execute(event);
	}


	public void setCommand(ICommand command, IEvent event) {
		this.command = command;
		this.event = event;
	}


}
