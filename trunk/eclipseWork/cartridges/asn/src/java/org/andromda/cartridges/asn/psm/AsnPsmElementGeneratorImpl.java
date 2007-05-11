// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package org.andromda.cartridges.asn.psm;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
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
    public AsnPsmElement getAsnElement(ModelElementFacade element, Map knownElements, Collection allElements)  
    {
    	if (knownElements.containsKey(element.getFullyQualifiedName())) {
    		return (AsnPsmElement)knownElements.get(element.getFullyQualifiedName());
    	}
    	
    	if (element instanceof ClassifierFacade) {
    		return getAsnElement((ClassifierFacade)element, knownElements, allElements);
    	} else if (element instanceof AssociationEndFacade ) {
    		return getAsnElement((AssociationEndFacade)element, knownElements, allElements);
    	} else if (element instanceof AssociationClassFacade ) {
    		return getAsnElement((AssociationClassFacade)element, knownElements, allElements);
    	} else if (element instanceof AssociationFacade ) {
    		return getAsnElement((AssociationFacade)element, knownElements, allElements);
    	} else if (element instanceof AttributeFacade ) {
    		return getAsnElement((AttributeFacade)element, knownElements, allElements);
    	} else if (element instanceof AttributeLinkFacade ) {
    		return getAsnElement((AttributeLinkFacade)element, knownElements, allElements);
    	} else {
    		String error="Unhandled ModelElementFacade: "+element.toString();
            throw new java.lang.UnsupportedOperationException(error);
    	}
    }

    
    
    /**
     * Creates a predefined AsnElement from a ModelElementFacade 
     * The Element doesn't have any subElements but will be stored in the 
     * Map of known Elements and the list of predefined elements.
     * That Element
     * @param element
     * @param knownElements
     * @param allElements
     * @return
     */
	@SuppressWarnings("unchecked")
    private AsnPsmElement newAsnElement(ModelElementFacade  element, Map knownElements, Collection allElements)
    {
		final String datatype = dataTypeMapping(element.getFullyQualifiedName()); 
    	if (knownElements.containsKey(datatype)) {
        	debug("found AsnElement: "+datatype);
    		return (AsnPsmElement)knownElements.get(datatype);
    	} else {
        	debug("build AsnElement: "+datatype);

        	AsnPsmElement result = new AsnPsmElement();
    		result.setDocumentation(element.getDocumentation("-- "));
        	result.setName(datatype);
        	result.setSubElements(new ArrayList<AsnPsmNameElementPair>());

        	knownElements.put(datatype, result);
        	allElements.add(result);

        	return result;
    	}
    }

    
    
    /**
     * @see org.andromda.cartridges.asn.psm.AsnPsmElementGenerator#getAsnElement(org.andromda.metafacades.uml.ClassifierFacade)
     */
	@Override
    public AsnPsmElement getAsnElement(ClassifierFacade element, Map knownElements, Collection allElements)  
    {
		//Warning: Removing this check will result in a unchecked recursive loop!
		final String datatype = dataTypeMapping(element.getFullyQualifiedName()); 
    	if (knownElements.containsKey(datatype)) {
    		return (AsnPsmElement)knownElements.get(datatype);
    	} 
    	
		AsnPsmElement result = newAsnElement(element, knownElements, allElements);
    	
    	//build Sub AsnElements
        @SuppressWarnings("unchecked")
    	Collection<AsnPsmNameElementPair> subElements = result.getSubElements();

        Collection col = element.getAllProperties();
    	Iterator it = col.iterator();
    	while(it.hasNext()){
    		ModelElementFacade m = (ModelElementFacade) it.next();
    		final String mDatatype = dataTypeMapping(element.getFullyQualifiedName());
    		debug("   with: "+mDatatype + " and name="+m.getName());
    		AsnPsmElement e = getAsnElement(m, knownElements, allElements);
    		if (e != null) {
    			AsnPsmNameElementPair pair = new AsnPsmNameElementPair();
    			pair.setName(m.getName());
    			pair.setElement(e);
        		subElements.add(pair);
    		}
    	}
    	result.setSubElements(subElements);

    	return result;
    }

    /**
     * @see org.andromda.cartridges.asn.psm.AsnPsmElementGenerator#getAsnElement(org.andromda.metafacades.uml.AssociationEndFacade)
     */
    @Override
    public AsnPsmElement getAsnElement(AssociationEndFacade element, Map knownElements, Collection allElements)
    {
    	return getAsnElement(element.getType(), knownElements, allElements);
    }

	/* (non-Javadoc)
	 * @see org.andromda.cartridges.asn.psm.AsnPsmElementGenerator#getAsnElement(org.andromda.metafacades.uml.AssociationFacade)
	 */
	@Override
	public AsnPsmElement getAsnElement(AssociationFacade element, Map knownElements, Collection allElements) 
	{
		error("getAsnElement(AssociationFacade element)  not finished");
		return null;
	}

	/* (non-Javadoc)
	 * @see org.andromda.cartridges.asn.psm.AsnPsmElementGenerator#getAsnElement(org.andromda.metafacades.uml.AssociationClassFacade)
	 */
	@Override
	public AsnPsmElement getAsnElement(AssociationClassFacade element, Map knownElements, Collection allElements) 
	{
		error("getAsnElement(AssociationClassFacade element)  not finished");
		return null;
	}

	/* (non-Javadoc)
	 * @see org.andromda.cartridges.asn.psm.AsnPsmElementGenerator#getAsnElement(org.andromda.metafacades.uml.AttributeFacade)
	 */
	@Override
	public AsnPsmElement getAsnElement(AttributeFacade element, Map knownElements, Collection allElements) 
	{
		return getAsnElement(element.getType(), knownElements, allElements);
	}


	/* (non-Javadoc)
	 * @see org.andromda.cartridges.asn.psm.AsnPsmElementGenerator#getAsnElement(org.andromda.metafacades.uml.AttributeLinkFacade)
	 */
	@Override
	public AsnPsmElement getAsnElement(AttributeLinkFacade element, Map knownElements, Collection allElements) 
	{
		error("getAsnElement(AttributeLinkFacade element)  not finished");
		return null;
	}

	/* (non-Javadoc)
	 * @see org.andromda.cartridges.asn.psm.AsnPsmElementGenerator#dataTypeMapping(java.lang.String)
	 */
	@Override
	public String dataTypeMapping(String original) {
		if (original.equals("java.lang.String")) return "VisibleString";
		if (original.equals("boolean")) return "BOOLEAN";
		if (original.equals("int")) return "INTEGER";
		error("Datatype: "+original);
		return original;
	}

}
