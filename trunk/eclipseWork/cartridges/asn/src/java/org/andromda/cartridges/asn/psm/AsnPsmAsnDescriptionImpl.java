// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package org.andromda.cartridges.asn.psm;

/**
 * @see org.andromda.cartridges.asn.psm.AsnPsmAsnDescription
 */
public class AsnPsmAsnDescriptionImpl
    extends org.andromda.cartridges.asn.psm.AsnPsmAsnDescription
{
    public AsnPsmAsnDescriptionImpl()
    {
        super();
    }

    public AsnPsmAsnDescriptionImpl(org.andromda.cartridges.asn.psm.AsnPsmHeaderDescription header, java.lang.String type, java.lang.String shortName, java.lang.String fullName, java.lang.String documentation)
    {
       super(header, type, shortName, fullName, documentation);
    }

    public AsnPsmAsnDescriptionImpl(java.lang.String type, java.lang.String shortName, java.lang.String fullName, java.lang.String documentation, java.util.Collection footer, org.andromda.cartridges.asn.psm.AsnPsmHeaderDescription header, java.util.Collection details)
    {
        super(type, shortName, fullName, documentation, footer, header, details);
    }

    /**
     * Copy-constructor from other AsnPsmAsnDescription
     *
     * @param otherBean, cannot be <code>null</code>
     * @throws java.lang.NullPointerException if the argument is <code>null</code>
     */
    public AsnPsmAsnDescriptionImpl(AsnPsmAsnDescription otherBean)
    {
        this(otherBean.getType(), otherBean.getShortName(), otherBean.getFullName(), otherBean.getDocumentation(), otherBean.getFooter(), otherBean.getHeader(), otherBean.getDetails());
    }

    /**
     * @see org.andromda.cartridges.asn.psm.AsnPsmAsnDescription#getAllBlocks()
     */
    public java.util.Collection getAllBlocks()
    {
        // @todo implement public java.util.Collection getAllBlocks()
        throw new java.lang.UnsupportedOperationException("org.andromda.cartridges.asn.psm.AsnPsmAsnDescription.getAllBlocks() Not implemented!");
    }

}
