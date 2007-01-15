package de.openaqua.base;


/**
 *
 * @author tukaram
 *
 */
public interface ICommandBuilder {
	/**
	 * @return reference to a new command instance
	 */
	public ICommand createCommand(int id);
}
