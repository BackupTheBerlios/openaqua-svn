package de.openaqua.base;


/**
 *
 * @model
 *
 */
public interface IMacro extends ICommand {
	/*
	 * @model type="Commands" containments="true"
	 */
	public void addCommand(Integer id);

	/*
	 * @model type="Commands" containments="true"
	 */
	public void clearCommands();
}
