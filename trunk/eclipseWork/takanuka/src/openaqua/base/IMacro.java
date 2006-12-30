package openaqua.base;

public interface IMacro extends ICommand {
	public void addCommand(ICommand cmd);
	public void clearCommands();
}
