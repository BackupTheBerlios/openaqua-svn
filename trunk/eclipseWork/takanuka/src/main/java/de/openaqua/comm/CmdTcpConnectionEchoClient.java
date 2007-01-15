/**
 *
 */
package de.openaqua.comm;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;
import org.apache.log4j.Logger;
import de.openaqua.comm.ATcpCommand;
import de.openaqua.comm.CTcpConnectionContext;

/**
 * A simple command. Expects a CTcpConnectionContext and
 * returns all incoming strings back to the sender
 *
 * Class is threadsafe and reentrant (What about the Logger?)
 *
 */
public class CmdTcpConnectionEchoClient extends ATcpCommand {
	private static Logger logger = Logger.getRootLogger();

	/**
	 *
	 */
	public CmdTcpConnectionEchoClient() {
		logger.debug("made new CmdTcpConnection()");
	}

	/* (non-Javadoc)
	 * @see openaqua.comm.ATcpCommand#execute(openaqua.comm.CTcpConnectionContext)
	 */
	@Override
	public boolean execute(CTcpConnectionContext context) {
		logger.debug("execute CmdTcpConnection with new Context");

		//check the context
		if (context == null) throw new NullPointerException("Got null reference as context");
		Socket socket = context.getSocket();
		if (socket == null) throw new NullPointerException("Got null reference as socket");

		try {
			//create some streams
			BufferedReader in = new BufferedReader( new InputStreamReader(socket.getInputStream()));
			OutputStream out = socket.getOutputStream();

			//print some helptext to the sender
			out.write("#################################\n".getBytes());
			out.write("#\n".getBytes());
			out.write("#\n".getBytes());
			out.write("# Echo: Returns all stuff back to the sender\n".getBytes());
			out.write("#       Finish with a single line \"bye\"\n".getBytes());
			out.write("#\n".getBytes());

			//make echos
			String line;
			logger.debug("Deal with input from " + socket.getInetAddress().toString());
			while ((line = in.readLine()) != null) {
				out.write(line.getBytes());
				out.write("\n".getBytes());
				if (line.equals("bye")) break;
			}

			//close everything
			logger.debug("Close socket");
			out.close();
			in.close();
			socket.close();

			//bye bye
			logger.debug("job done");
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
