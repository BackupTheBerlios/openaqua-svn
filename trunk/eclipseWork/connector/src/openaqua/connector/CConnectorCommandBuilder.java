/**
 * 
 */
package openaqua.connector;


import openaqua.base.CCommandBuilder;
import openaqua.base.CMacro;
import openaqua.base.ICommand;
import openaqua.comm.CmdTcpConnectionEchoClient;

/**
 * @author tukaram
 *
 */
public class CConnectorCommandBuilder extends CCommandBuilder {

	/* (non-Javadoc)
	 * 
	 * 5000 - CmdCreateUid()
	 * @see openaqua.base.CFactoryCommands#createCommand(java.lang.Integer)
	 */
	@Override
	public ICommand createCommand(int id) {

		if (id == 5000) return new CmdCreateUid();
		if (id == 5001) return new CmdTcpConnectionEchoClient();
		if (id == 6000) {
			CMacro m = new CMacro();
			m.addCommand(5000);
			m.addCommand(1);
			return m;
		}
		
		return null;
	}
}
