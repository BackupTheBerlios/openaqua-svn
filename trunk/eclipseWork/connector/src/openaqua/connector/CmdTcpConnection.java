/**
 * 
 */
package openaqua.connector;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;
import org.apache.log4j.Logger;
import openaqua.comm.ATcpCommand;
import openaqua.comm.CTcpConnectionContext;

/**
 * @author behrenan
 *
 */
public class CmdTcpConnection extends ATcpCommand {
	private static Logger logger = Logger.getRootLogger();

	/**
	 * 
	 */
	public CmdTcpConnection() {
		logger.debug("made new CmdTcpConnection()");
	}

	/* (non-Javadoc)
	 * @see openaqua.comm.ATcpCommand#execute(openaqua.comm.CTcpConnectionContext)
	 */
	@Override
	public boolean execute(CTcpConnectionContext context) {
		logger.debug("execute CmdTcpConnection with new Context");

		Socket socket = context.getSocket();
		if (socket == null) throw new NullPointerException("Got null reference as socket");

		try {
			BufferedReader in = new BufferedReader( new InputStreamReader(socket.getInputStream()));
			OutputStream out = socket.getOutputStream();
			String line;
			while ((line = in.readLine()) != null) {	
				out.write(line.getBytes());
				out.write("\n".getBytes());
				if (line.equals("bye")) break;
			}
			out.close();
			in.close();
			socket.close();
			return true;
		} catch (IOException e) {
			logger.error("IOException while working with socket object: " + e.getLocalizedMessage());
			e.printStackTrace();
			try {
				socket.close();
			} catch (IOException c) {
				logger.error("IOException closing socket: " + c.getLocalizedMessage());
				c.printStackTrace();
			}
		}
		
		return false;
	}


}
