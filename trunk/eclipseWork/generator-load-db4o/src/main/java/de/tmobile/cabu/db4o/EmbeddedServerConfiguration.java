package de.tmobile.cabu.db4o;

public class EmbeddedServerConfiguration {
	final private String   filename ;

	private EmbeddedServerConfiguration() {
		super();
		filename = null;
	}
	
	public EmbeddedServerConfiguration(final String filename) {
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