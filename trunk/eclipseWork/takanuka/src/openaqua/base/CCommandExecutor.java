package openaqua.base;


final public class CCommandExecutor implements Runnable  {
	private ICommand command;
	private IRecord record;

	public CCommandExecutor() {
		super();
	}
	
	
	public void run() {
		command.execute(record);
	}


	public void setCommand(ICommand command, IRecord record) {
		this.command = command;
		this.record = record;
	}


}
