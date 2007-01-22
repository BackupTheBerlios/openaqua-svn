/**
 * 
 */
package de.tmobile.cabu.db4o;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;

/**
 * @author behrenan
 *
 */
public class AlmaGenerator extends Thread{
	private OutputStream outStream= null; 
	private Socket clientSocket = null;
	private InputStream resStream = null;
	private byte[] rawBuffer = null;
	private byte[] readBuffer = new byte[ 1000 ];


	/**
	 * Constructor
	 * @throws IOException 
	 * @throws UnknownHostException 
	 */
	public AlmaGenerator(byte[] rawBuffer, String threadName) throws UnknownHostException, IOException {
		super( threadName); 
		this.rawBuffer = rawBuffer;
		clientSocket = new Socket( Configuration.getInstance().getAlmaHost(), Configuration.getInstance().getAlmaPort());
		outStream = clientSocket.getOutputStream();
		resStream = clientSocket.getInputStream();

	}


	/**
	 * Init this thread
	 *
	 */
	public void Init(){
	}




	private boolean executeRead()  {
		try {
			outStream.write(rawBuffer);
			resStream.read(readBuffer);
		} catch (IOException e) {
			System.err.println("Error in execution: " + e.getLocalizedMessage());
			return false;
		}
		return true;
	}



	/**
	 * The thread execution method
	 * runs endless
	 */
	public void run () {
		for (int i = 0; i < Configuration.getInstance().getReqLoops(); i++){
			if (executeRead() != true) {return;	}
			Stats.getInstance().addReadResults(1);
		}

	}
}
