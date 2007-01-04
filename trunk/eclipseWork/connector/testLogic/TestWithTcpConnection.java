
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;

import junit.framework.TestCase;

import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;

/**
 * @author behrenan
 *
 */
public class TestWithTcpConnection extends TestCase {

	static Socket socket;
	/**
	 * @throws java.lang.Exception
	 */
	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
		socket = new Socket( "localhost", 12345 );
	}

	/**
	 * @throws java.lang.Exception
	 */
	@AfterClass
	public static void tearDownAfterClass() throws Exception {
		if (socket != null) {
			socket.close();
		}
	}

	@Test
	public final void testTcpConnection() {
		try {
			socket = new Socket( "localhost", 12345 );
			assertNotNull(socket);
			BufferedReader in = new BufferedReader( new InputStreamReader(socket.getInputStream()));
			OutputStream out  = socket.getOutputStream();
			
			//send recieve something
			out.write("Hallo".getBytes());
			String line;
			if ((line = in.readLine()) != null) {
				System.out.println(line);
				assertEquals("Hallo", line);
			}

			//send recieve something
			out.write("bye".getBytes());
			if ((line = in.readLine()) != null) {
				System.out.println(line);
				assertEquals("bye", line);
			}
			
			
			out.close();
			in.close();
			socket.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
}
