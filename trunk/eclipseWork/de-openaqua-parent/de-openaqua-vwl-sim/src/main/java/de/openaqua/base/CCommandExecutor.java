package de.openaqua.base;


final public class CCommandExecutor implements Runnable  {
	private ICommand command;
	private IContext context;

	public CCommandExecutor() {
		super();
	}


	public void run() {
		command.execute(context);
	}


	public void setCommand(ICommand command, IContext context) {
		this.command = command;
		this.context = context;
	}


}
