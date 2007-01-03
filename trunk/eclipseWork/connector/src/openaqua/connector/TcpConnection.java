/**
 * 
 */
package openaqua.connector;


import java.net.*; 
import java.io.*; 

/**
 * @author behrenan
 *
 */
public class TcpConnection {
	int port = 12345;
	ServerSocket server = null; 

	TcpConnection() throws IOException {
		super();
		server = new ServerSocket(port);
	}


	protected void handleConnection(Socket socket) {
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
		} catch (IOException e) {
			e.printStackTrace();
			try {
				socket.close();
			} catch (IOException e1) {
				;//do nothing
			}
		}
		return;
	}
	public void waitForConnection(){
		try {
			while(true) {
				handleConnection(server.accept());
			}
		} catch (IOException e) {
			e.printStackTrace();
			return;
		}
	}

}
