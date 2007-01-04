/**
 * 
 */
package openaqua.base;

/**
 * @author tukaram
 *
 */
public interface ICommand {
	public boolean execute(final IEvent event);
}
