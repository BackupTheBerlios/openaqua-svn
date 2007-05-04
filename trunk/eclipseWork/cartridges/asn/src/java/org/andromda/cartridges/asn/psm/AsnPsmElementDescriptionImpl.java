// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package org.andromda.cartridges.asn.psm;

/**
 * @see org.andromda.cartridges.asn.psm.AsnPsmElementDescription
 */
public abstract class AsnPsmElementDescriptionImpl
    extends org.andromda.cartridges.asn.psm.AsnPsmElementDescription
{
    public AsnPsmElementDescriptionImpl()
    {
        super();
    }

    public AsnPsmElementDescriptionImpl(java.lang.String name, java.lang.String type)
    {
        super(name, type);
    }

    /**
     * Copy-constructor from other AsnPsmElementDescription
     *
     * @param otherBean, cannot be <code>null</code>
     * @throws java.lang.NullPointerException if the argument is <code>null</code>
     */
    public AsnPsmElementDescriptionImpl(AsnPsmElementDescription otherBean)
    {
        this(otherBean.getName(), otherBean.getType());
    }

    /**
     * @see org.andromda.cartridges.asn.psm.AsnPsmElementDescription#buildFromClassifier(org.andromda.metafacades.uml.ClassifierFacade)
     */
    public boolean buildFromClassifier(org.andromda.metafacades.uml.ClassifierFacade classifier)
    {
        // @todo implement public boolean buildFromClassifier(org.andromda.metafacades.uml.ClassifierFacade classifier)
        throw new java.lang.UnsupportedOperationException("org.andromda.cartridges.asn.psm.AsnPsmElementDescription.buildFromClassifier(org.andromda.metafacades.uml.ClassifierFacade classifier) Not implemented!");
    }

}
