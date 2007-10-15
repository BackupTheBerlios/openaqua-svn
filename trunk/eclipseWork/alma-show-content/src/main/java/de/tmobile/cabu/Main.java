/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class Main {
	static TTConnection mainConnection = null;

	final private static Logger logger = Logger.getRootLogger();

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		AlmaConnection alma;
		try {
			
			alma = new AlmaConnection();
			//alma.Connect("DSN=RunData"); //!Achtung: Braucht Client-Treiber
			alma.Connect("jdbc:timesten:direct:RunData");
			//alma.Connect("jdbc:timesten:direct:pALMA62a");
			alma.listTemplates();
			alma.Disconnect();
		} catch (ClassNotFoundException e) {
			logger.error("Class not Found");
			e.printStackTrace();
			return;
		}

	}
}
