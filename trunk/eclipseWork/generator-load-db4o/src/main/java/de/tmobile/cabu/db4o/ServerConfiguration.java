package de.tmobile.cabu.db4o;

public class ServerConfiguration {
	final private String   filename ;

	private ServerConfiguration() {
		super();
		filename = null;
	}
	
	public ServerConfiguration(final String filename) {
		super();
		this.filename = filename;
	}

	/**
	 * @return the filename
	 */
	public final String getFilename() {
		return filename;
	}

}