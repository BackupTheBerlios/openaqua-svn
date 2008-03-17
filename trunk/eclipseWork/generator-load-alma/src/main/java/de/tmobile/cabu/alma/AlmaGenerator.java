/**
 * 
 */
package de.tmobile.cabu.alma;


import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;


/**
 * @author behrenan
 * 
 */
public class AlmaGenerator extends Thread {
	private OutputStream outStream = null;
	private Socket clientSocket = null;
	private InputStream resStream = null;
	private byte[] rawBuffer = null;
	private final byte[] readBuffer = new byte[1000];


	/**
	 * Constructor
	 * 
	 * @throws IOException
	 * @throws UnknownHostException
	 */
	public AlmaGenerator(final byte[] rawBuffer, final String threadName) throws UnknownHostException, IOException {
		super(threadName);
		this.rawBuffer = rawBuffer;

		clientSocket = new Socket(Configuration.getInstance().getAlmaHost(), Configuration.getInstance().getAlmaPort());

		outStream = clientSocket.getOutputStream();
		resStream = clientSocket.getInputStream();
		System.out.println("Thread " + threadName + " created");

	}


	private boolean executeRead() {
		try {
			outStream.write(rawBuffer);
			resStream.read(readBuffer);
		} catch (final IOException e) {
			return false;
		}
		return true;
	}


	/**
	 * Init this thread
	 * 
	 */
	public void Init() {}


	/**
	 * The thread execution method runs endless
	 */
	@Override
	public void run() {
		for (int i = 0; i < Configuration.getInstance().getReqLoops(); i++) {
			if (executeRead() != true) { return; }
			Stats.getInstance().addReadResults(1);

			//let the thread sleep
			try {
				sleep(Configuration.getInstance().getSleepTime());
			} catch (final InterruptedException e) {
				e.printStackTrace();
			}
		}

	}
}
