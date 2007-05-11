// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package org.andromda.cartridges.asn.psm;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;
import java.util.Map;

import org.andromda.metafacades.uml.AssociationClassFacade;
import org.andromda.metafacades.uml.AssociationEndFacade;
import org.andromda.metafacades.uml.AssociationFacade;
import org.andromda.metafacades.uml.AttributeFacade;
import org.andromda.metafacades.uml.AttributeLinkFacade;
import org.andromda.metafacades.uml.ClassifierFacade;
import org.andromda.metafacades.uml.ModelElementFacade;

/**
 * @see org.andromda.cartridges.asn.psm.AsnPsmElementGenerator
 */

public class AsnPsmElementGeneratorImpl
    extends org.andromda.cartridges.asn.psm.AsnPsmElementGenerator
{
    public AsnPsmElementGeneratorImpl()
    {
        super();
    }

    /**
     * Copy-constructor from other AsnPsmElementGenerator
     *
     * @param otherBean, cannot be <code>null</code>
     * @throws java.lang.NullPointerException if the argument is <code>null</code>
     */
    public AsnPsmElementGeneratorImpl(AsnPsmElementGenerator otherBean)
    {
        this();
    }

    /**
     * @see org.andromda.cartridges.asn.psm.AsnPsmElementGenerator#getAsnElement(org.andromda.metafacades.uml.ModelElementFacade)
     */
    @Override
    public AsnPsmElement getAsnElement(org.andromda.metafacades.uml.ModelElementFacade element, Map knownElements)  
    {
    	
    	if (knownElements.containsKey(element.getFullyQualifiedName())) {
    		return (AsnPsmElement)knownElements.get(element.getFullyQualifiedName());
    	}
    	if (element instanceof ClassifierFacade) {
    		return getAsnElement((ClassifierFacade)element, knownElements);
    	} else if (element instanceof AssociationEndFacade ) {
    		return getAsnElement((AssociationEndFacade)element, knownElements);
    	} else if (element instanceof AssociationClassFacade ) {
    		return getAsnElement((AssociationClassFacade)element, knownElements);
    	} else if (element instanceof AssociationFacade ) {
    		return getAsnElement((AssociationFacade)element, knownElements);
    	} else if (element instanceof AttributeFacade ) {
    		return getAsnElement((AttributeFacade)element, knownElements);
    	} else if (element instanceof AttributeLinkFacade ) {
    		return getAsnElement((AttributeLinkFacade)element, knownElements);
    	} else {
    		String error="Unhandled ModelElementFacade: "+element.toString();
            throw new java.lang.UnsupportedOperationException(error);
    	}
    }

    /**
     * @see org.andromda.cartridges.asn.psm.AsnPsmElementGenerator#getAsnElement(org.andromda.metafacades.uml.ClassifierFacade)
     */
    @Override
    public AsnPsmElement getAsnElement(ClassifierFacade element, Map knownElements)  
    {
    	if (knownElements.containsKey(element.getFullyQualifiedName())) {
    		return (AsnPsmElement)knownElements.get(element.getFullyQualifiedName());
    	}

    	debug("build cAsnElement: "+element.getFullyQualifiedName());
    	AsnPsmElement result = new AsnPsmElement();
    	knownElements.put(element.getFullyQualifiedName(), result);
    	result.setDocumentation(element.getDocumentation("-- "));
    	result.setName(element.getName());
    	result.setFullQualifiedName(element.getFullyQualifiedName());

    	//build Sub AsnElements
    	Collection<AsnPsmElement> subElements = new ArrayList<AsnPsmElement>(); 
    	Collection col = element.getAllProperties();
    	Iterator it = col.iterator();
    	while(it.hasNext()){
    		ModelElementFacade m = (ModelElementFacade) it.next();
    		debug("   with: "+m.getFullyQualifiedName());
    		AsnPsmElement e = getAsnElement(m, knownElements);
    		if (e != null) {
        		subElements.add(e);
    		}
    	}
    	result.setSubElements(subElements);

    	return result;
    }

    /**
     * @see org.andromda.cartridges.asn.psm.AsnPsmElementGenerator#getAsnElement(org.andromda.metafacades.uml.AssociationEndFacade)
     */
    @Override
    public AsnPsmElement getAsnElement(AssociationEndFacade element, Map knownElements)
    {
    	return getAsnElement(element.getType(), knownElements);
    }

	/* (non-Javadoc)
	 * @see org.andromda.cartridges.asn.psm.AsnPsmElementGenerator#getAsnElement(org.andromda.metafacades.uml.AssociationFacade)
	 */
	@Override
	public AsnPsmElement getAsnElement(AssociationFacade element, Map knownElements) 
	{
		error("getAsnElement(AssociationFacade element) not finished: " + element.getFullyQualifiedName());
		List list = element.getAssociationEnds();
		ListIterator it = list.listIterator();
		while(it.hasNext()) {
			AssociationEndFacade end = (AssociationEndFacade) it.next();
			error("has end: " +end.getFullyQualifiedName());
			
		}
		return null;
	}

	/* (non-Javadoc)
	 * @see org.andromda.cartridges.asn.psm.AsnPsmElementGenerator#getAsnElement(org.andromda.metafacades.uml.AssociationClassFacade)
	 */
	@Override
	public AsnPsmElement getAsnElement(AssociationClassFacade element, Map knownElements) 
	{
		error("getAsnElement(AssociationClassFacade element)  not finished");
		return null;
	}

	/* (non-Javadoc)
	 * @see org.andromda.cartridges.asn.psm.AsnPsmElementGenerator#getAsnElement(org.andromda.metafacades.uml.AttributeFacade)
	 */
	@Override
	public AsnPsmElement getAsnElement(AttributeFacade element, Map knownElements) 
	{
		return getAsnElement(element.getType(), knownElements);
	}


	/* (non-Javadoc)
	 * @see org.andromda.cartridges.asn.psm.AsnPsmElementGenerator#getAsnElement(org.andromda.metafacades.uml.AttributeLinkFacade)
	 */
	@Override
	public AsnPsmElement getAsnElement(AttributeLinkFacade element, Map knownElements) 
	{
		error("getAsnElement(AttributeLinkFacade element)  not finished");
		return null;
	}

}
