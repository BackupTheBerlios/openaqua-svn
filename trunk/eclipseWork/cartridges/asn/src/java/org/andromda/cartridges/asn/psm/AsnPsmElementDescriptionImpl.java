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

    public AsnPsmElementDescriptionImpl(java.lang.String type, java.lang.String shortName, java.lang.String fullName, java.lang.String documentation)
    {
        super(type, shortName, fullName, documentation);
    }

    /**
     * Copy-constructor from other AsnPsmElementDescription
     *
     * @param otherBean, cannot be <code>null</code>
     * @throws java.lang.NullPointerException if the argument is <code>null</code>
     */
    public AsnPsmElementDescriptionImpl(AsnPsmElementDescription otherBean)
    {
        this(otherBean.getType(), otherBean.getShortName(), otherBean.getFullName(), otherBean.getDocumentation());
    }

    /**
     * @see org.andromda.cartridges.asn.psm.AsnPsmElementDescription#buildFromClassifier(org.andromda.metafacades.uml.ClassifierFacade)
     */
    public boolean buildFromClassifier(org.andromda.metafacades.uml.ClassifierFacade classifier)
    {
    	boolean result;
    	
    	if (classifier == null){
    		error("got null reference as classifier");
    		result = false;
    	} else {
        	this.setFullName(classifier.getFullyQualifiedName().replaceAll("\\.", "/"));
        	this.setShortName(classifier.getName());
        	this.setDocumentation(classifier.getDocumentation("-- "));
        	result = true;
    	}

    	return result;
    }

}
