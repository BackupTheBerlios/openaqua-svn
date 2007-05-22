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
import java.util.TreeMap;

import org.andromda.metafacades.uml.ModelElementFacade;

/**
 * @see org.andromda.cartridges.asn.psm.AsnPsmAsnDescriptionGenerator
 */
public class AsnPsmAsnDescriptionGeneratorImpl
    extends org.andromda.cartridges.asn.psm.AsnPsmAsnDescriptionGenerator
{
    public AsnPsmAsnDescriptionGeneratorImpl()
    {
        super();
    }

    
    
    /**
     * Copy-constructor from other AsnPsmAsnDescriptionGenerator
     *
     * @param otherBean, cannot be <code>null</code>
     * @throws java.lang.NullPointerException if the argument is <code>null</code>
     */
    public AsnPsmAsnDescriptionGeneratorImpl(AsnPsmAsnDescriptionGenerator otherBean)
    {
        this();
    }

    
    
    
    /**
     * @see org.andromda.cartridges.asn.psm.AsnPsmAsnDescriptionGenerator#buildDescription(org.andromda.metafacades.uml.ClassifierFacade)
     * TODO Exception in case of errors?
     */
    public org.andromda.cartridges.asn.psm.AsnPsmAsnDescription buildDescription(org.andromda.metafacades.uml.ClassifierFacade classifier)
    {
		AsnPsmElementGenerator elementGenerator = new AsnPsmElementGeneratorImpl();
    	debug("build AsnDescription: "+elementGenerator.dataTypeMapping(classifier.getFullyQualifiedName(),0));
    	
    	
    	//create a new Description object
    	AsnPsmAsnDescription desc = new AsnPsmAsnDescription();
    	
    	//setup primary data
    	desc.setDocumenation(classifier.getDocumentation("-- "));
    	desc.setName(classifier.getName());
    	desc.setPackageName(classifier.getPackagePath()+"/"+classifier.getName());

    	//variables for Elements
    	Collection<AsnPsmElement> subElements = new ArrayList<AsnPsmElement>();
    	Map<String, AsnPsmElement> knownElements = new TreeMap<String, AsnPsmElement>();
    	
    	//build AsnElements
    	Collection col = classifier.getAllAssociatedClasses();
    	Iterator it = col.iterator();
    	while(it.hasNext()){
    		ModelElementFacade m = (ModelElementFacade) it.next();
    		debug("add subElement: "+m.getFullyQualifiedName(), 1);
    		subElements.add(elementGenerator.getAsnElement(m, knownElements, 2));
    	}
    
    	desc.setSubElements(subElements);
    	desc.setKnownElements(knownElements);
    	
    	
    	return desc;

    }
}
