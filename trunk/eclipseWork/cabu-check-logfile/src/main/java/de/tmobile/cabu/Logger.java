/**
 * 
 */
package de.tmobile.cabu;

import java.net.InetAddress;
import java.net.UnknownHostException;


/**
 * @author behrenan
 * 
 */
public final class Logger {

	private static Logger INSTANCE = new Logger();


	private Logger() {
		super();
	}
	
	static public Logger getRootLogger() {
		return INSTANCE;
	}


	public void header()  {
		out("============================================================");
	}

	public void smallHeader()  {
		out("------------------------------------------------------------");
	}

	public void empty()  {
		out("");
	}

	public void debug(final String text) {
		System.err.println("DBG " + text);
	}

	public void info(final String text) {
		System.err.println("INF " + text);
	}

	public void error(final String text) {
		System.err.println("ERR " + text);
	}

	public void warn(final String text) {
		System.err.println("WRN " + text);
	}

	public void out(final String text)  {
		System.out.println(text);
	}

	public void printHeader() {
		
		
		String hostname = "<unknown>";
		String fqhostname = "<unknown>";
		String ip = "<unknown>";
		try {
			hostname = InetAddress.getLocalHost().getHostName();
			fqhostname = InetAddress.getLocalHost().getCanonicalHostName();
			ip = InetAddress.getLocalHost().getHostAddress();
			
		} catch (UnknownHostException e) {
			Logger.getRootLogger().error("Cannot resolv hostname");
			e.printStackTrace();
		}


		
		
		header();
		empty();
		out("Output basing on file " + Configuration.getInstance().getLogFile());
		out("Output for system " + hostname + " ("+fqhostname+")");
		out("with IP " + ip);
		empty();

	}
	
}
