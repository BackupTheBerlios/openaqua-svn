// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package org.andromda.cartridges.asn.psm;

import org.apache.log4j.Logger;

/**
 * @see org.andromda.cartridges.asn.psm.AsnLogger
 */
public class AsnLoggerImpl
    extends org.andromda.cartridges.asn.psm.AsnLogger
{
	final private Logger logger = Logger.getLogger("cartridge:asn");
    public AsnLoggerImpl()
    {
        super();
    }

    /**
     * Copy-constructor from other AsnLogger
     *
     * @param otherBean, cannot be <code>null</code>
     * @throws java.lang.NullPointerException if the argument is <code>null</code>
     */
    public AsnLoggerImpl(AsnLogger otherBean)
    {
        this();
    }

    /**
     * @see org.andromda.cartridges.asn.psm.AsnLogger#error(java.lang.String)
     */
	@Override
    public void error(java.lang.String msg)
    {
    	logger.error(msg);
    }

    /**
     * @see org.andromda.cartridges.asn.psm.AsnLogger#warn(java.lang.String)
     */
	@Override
    public void warn(java.lang.String msg)
    {
    	logger.warn(msg);
    }

    /**
     * @see org.andromda.cartridges.asn.psm.AsnLogger#info(java.lang.String)
     */
	@Override
    public void info(java.lang.String msg)
    {
    	logger.info(msg);
    }

	/* (non-Javadoc)
	 * @see org.andromda.cartridges.asn.psm.AsnLogger#fatal(java.lang.String)
	 */
	@Override
	public void fatal(String msg) {
		logger.fatal(msg);		
	}

	/* (non-Javadoc)
	 * @see org.andromda.cartridges.asn.psm.AsnLogger#debug(java.lang.String, java.lang.Integer)
	 */
	@Override
	public void debug(String msg, Integer level) {
		String spaces = "";
		for (int i=0;i<level;i++) spaces += "   ";
		logger.debug(spaces + msg);
	}

	/* (non-Javadoc)
	 * @see org.andromda.cartridges.asn.psm.AsnLogger#debug(java.lang.String)
	 */
	@Override
	public void debug(String msg) {
		debug(msg, 0);		
	}

}
