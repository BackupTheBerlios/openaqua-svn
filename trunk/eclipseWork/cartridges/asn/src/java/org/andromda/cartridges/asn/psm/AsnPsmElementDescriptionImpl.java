// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package org.andromda.cartridges.asn.psm;

import java.util.Collection;
import java.util.Iterator;

import org.andromda.metafacades.uml.ClassifierFacade;

/**
 * @see org.andromda.cartridges.asn.psm.AsnPsmElementDescription
 */
public abstract class AsnPsmElementDescriptionImpl
    extends org.andromda.cartridges.asn.psm.AsnPsmElementDescription
{
	;
	
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


    public  void listAssocs(org.andromda.metafacades.uml.ClassifierFacade classifier) {
    	warn("List Assocs for"+classifier.getName());
    	Collection a = classifier.getAssociationEnds();
    	Iterator it = a.iterator();
    	while (it.hasNext()) {
    		Object o = it.next();
    		if (o instanceof org.andromda.metafacades.uml.ClassifierFacade) {
        		org.andromda.metafacades.uml.ClassifierFacade c = (ClassifierFacade) o; 
        		error("assoc: " + c.getName());
        		//listAssocs(c);
    		}
    	}
    }

    public void listProperties(org.andromda.metafacades.uml.ClassifierFacade classifier) {
    	warn("List Properties for"+classifier.getName());
    	Collection a = classifier.getProperties();
    	Iterator it = a.iterator();
    	while (it.hasNext()) {
    		Object o = it.next();
    		if (o instanceof org.andromda.metafacades.uml.ClassifierFacade) {
        		org.andromda.metafacades.uml.ClassifierFacade c = (ClassifierFacade) o; 
        		error("property: " + c.getName());
    		}
    	}
    }

    public void listAttributes(org.andromda.metafacades.uml.ClassifierFacade classifier) {
    	warn("List Attributes for"+classifier.getName());
    	Collection a = classifier.getAttributes();
    	Iterator it = a.iterator();
    	while (it.hasNext()) {
    		Object o = it.next();
    		error("attributes: " + o.toString());
    	}
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
