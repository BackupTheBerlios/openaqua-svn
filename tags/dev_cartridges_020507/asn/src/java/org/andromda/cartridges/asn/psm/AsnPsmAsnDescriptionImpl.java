// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package org.andromda.cartridges.asn.psm;

import org.apache.log4j.Logger;

/**
 * @see org.andromda.cartridges.asn.psm.AsnPsmAsnDescription
 */
public class AsnPsmAsnDescriptionImpl
    extends org.andromda.cartridges.asn.psm.AsnPsmAsnDescription
{
	final Logger logger = Logger.getRootLogger();
	public AsnPsmAsnDescriptionImpl()
    {
        super();
        logger.error("ERZEUGE AsnPsmAsnDescriptionImpl");
    }

    public AsnPsmAsnDescriptionImpl(java.lang.String name)
    {
       super(name);
       logger.error("ERZEUGE AsnPsmAsnDescriptionImpl");
    }

    public AsnPsmAsnDescriptionImpl(java.lang.String name, java.util.Collection detailDesc, java.util.Collection headerDesc, java.util.Collection footerDesc)
    {
        super(name, detailDesc, headerDesc, footerDesc);
        logger.error("ERZEUGE AsnPsmAsnDescriptionImpl");
    }

    /**
     * Copy-constructor from other AsnPsmAsnDescription
     *
     * @param otherBean, cannot be <code>null</code>
     * @throws java.lang.NullPointerException if the argument is <code>null</code>
     */
    public AsnPsmAsnDescriptionImpl(AsnPsmAsnDescription otherBean)
    {
        this(otherBean.getName(), otherBean.getDetailDesc(), otherBean.getHeaderDesc(), otherBean.getFooterDesc());
    }

    /**
     * @see org.andromda.cartridges.asn.psm.AsnPsmAsnDescription#getAllBlocks()
     */
    public java.util.Collection getAllBlocks()
    {
        // @todo implement public java.util.Collection getAllBlocks()
        throw new java.lang.UnsupportedOperationException("org.andromda.cartridges.asn.psm.AsnPsmAsnDescription.getAllBlocks() Not implemented!");
    }

    /**
     * @see org.andromda.cartridges.asn.psm.AsnPsmAsnDescription#getHeader()
     */
    public java.util.Collection getHeader()
    {
        // @todo implement public java.util.Collection getHeader()
        throw new java.lang.UnsupportedOperationException("org.andromda.cartridges.asn.psm.AsnPsmAsnDescription.getHeader() Not implemented!");
    }

    /**
     * @see org.andromda.cartridges.asn.psm.AsnPsmAsnDescription#getFooter()
     */
    public java.util.Collection getFooter()
    {
        // @todo implement public java.util.Collection getFooter()
        throw new java.lang.UnsupportedOperationException("org.andromda.cartridges.asn.psm.AsnPsmAsnDescription.getFooter() Not implemented!");
    }

    /**
     * @see org.andromda.cartridges.asn.psm.AsnPsmAsnDescription#getDetails()
     */
    public java.util.Collection getDetails()
    {
        // @todo implement public java.util.Collection getDetails()
        throw new java.lang.UnsupportedOperationException("org.andromda.cartridges.asn.psm.AsnPsmAsnDescription.getDetails() Not implemented!");
    }

}
