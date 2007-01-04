/**
 * 
 */
package openaqua.comm;

import openaqua.base.ICommand;
import openaqua.base.IContext;


/**
 * @author behrenan
 *
 */
public abstract class ATcpCommand implements ICommand {

	public abstract boolean execute(CTcpConnectionContext context);
	
	public boolean execute(IContext context) {
		if (context == null) throw new NullPointerException("got null pointer reference as CTcpConnectionContext");
		if (context instanceof CTcpConnectionContext) {
			return execute((CTcpConnectionContext)context);
		} else {
			throw new IllegalArgumentException("TcpCommand got no CTcpConnectionContext context object");
		}
	}
	
}
