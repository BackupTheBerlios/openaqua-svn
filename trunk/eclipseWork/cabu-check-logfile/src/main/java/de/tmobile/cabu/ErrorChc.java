/**
 * 
 */
package de.tmobile.cabu;

/**
 * @author behrenan
 * 
 */
public class ErrorChc {
	private static ErrorChc	INSTANCE	= new ErrorChc();


	public static ErrorChc getInstance() {
		return INSTANCE;
	}

	private int	errCounterLocked	= 0;

	private int	errNoPricelist	 = 0;


	/**
	 * @return the errCounterLocked
	 */
	public int getErrCounterLocked() {
		return errCounterLocked;
	}


	/**
	 * @return the errNoPricelist
	 */
	public int getErrNoPricelist() {
		return errNoPricelist;
	}


	public void increaseErrCounterLocked() {
		errCounterLocked++;
	}


	public void increaseErrNoPricelist() {
		errNoPricelist++;
	}


	public void print() {
		if (Configuration.getInstance().getLogFileType() != 1) { return; }
		final Logger log = Logger.getRootLogger();
		log.smallHeader();

		log.empty();
		if (errCounterLocked > 0) {
			log.out("Found " + errCounterLocked + " Errors about locked Counter");
			log.out("      (this kind of error can be ignored usually)");
			log.empty();
		}
		if (errNoPricelist > 0) {
			log.out("Found " + errNoPricelist + " Errors with pricelist problems");
			log.out("      (Check the Xoxi Logfile for better information)");
			log.empty();

		}
	}
}
