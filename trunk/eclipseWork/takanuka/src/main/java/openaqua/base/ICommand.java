/**
 * 
 */
package openaqua.base;

/**
 * @author tukaram
 * @model
 */
public interface ICommand {
	/*
	 * @model type="Command"
	 */
	public boolean execute(final IContext context);
}
