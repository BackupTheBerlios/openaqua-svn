/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class CAlmaFileWriter extends CAlmaDataLoader {
	private static CAlmaFileWriter INSTANCE = new CAlmaFileWriter();

	public static CAlmaFileWriter getInstances() {
		return INSTANCE;
	}


	protected CAlmaFileWriter() {
		super();
	}

	@Override
	public Thread makeNewThread(final String name, final BaseList list) {
		return new Thread(new CAlmaFileWriterThread(name, list));
	}


}
