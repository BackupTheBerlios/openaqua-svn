/**
 *
 */
package de.openaqua.comm;

import de.openaqua.base.ICommand;
import de.openaqua.base.IContext;


/**
 *
 * Default implementation for a TcpCommand in a TcpServer environment
 *
 * Class is threadsafe and reentrant
 *
 */
public abstract class ATcpCommand implements ICommand {

	/**
	 *
	 * The method will be executed in a threaded environment!<br>
	 *
	 * If this method will be overriden thread safity must be guaranteed
	 *
	 * @param context a Context with an Tcp Socket in it
	 * @return
	 */
	public abstract boolean execute(CTcpConnectionContext context);


	/**
	 *
	 * Function checks arguments and calls execute(CTcpConnectionContext context)
	 *
	 * @throws NullPointerException - if context is null
	 * @throws IllegalArgumentException - if context is not a CTcpConnectionContext
	 */
	final public boolean execute(IContext context) {
		if (context == null) throw new NullPointerException("got null pointer reference as CTcpConnectionContext");
		if (context instanceof CTcpConnectionContext) {
			return execute((CTcpConnectionContext)context);
		} else {
			throw new IllegalArgumentException("TcpCommand got no CTcpConnectionContext context object");
		}
	}

}
