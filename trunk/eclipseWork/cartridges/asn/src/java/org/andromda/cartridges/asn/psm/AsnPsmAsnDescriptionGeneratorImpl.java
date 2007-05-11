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
    	debug("build AsnDescription: "+classifier.getFullyQualifiedName());
    	AsnPsmAsnDescription desc = new AsnPsmAsnDescription();
    	desc.setDocumenation(classifier.getDocumentation("-- "));
    	desc.setName(classifier.getName());
    	desc.setPackageName(classifier.getPackagePath());
    	Collection<AsnPsmElement> allElements = new ArrayList<AsnPsmElement>();
    	Map<String, AsnPsmElement> knownElements = new TreeMap<String, AsnPsmElement>();
    	
    	//build AsnElements
    	Collection col = classifier.getAllProperties();
    	Iterator it = col.iterator();
    	while(it.hasNext()){
    		AsnPsmElementGenerator elementGenerator = new AsnPsmElementGeneratorImpl();
    		ModelElementFacade m = (ModelElementFacade) it.next();
    		debug("   with: "+m.getFullyQualifiedName());
    		elementGenerator.getAsnElement(m, knownElements, allElements);
    	}
    	desc.setAllElements(allElements);
    	return desc;
    }
}
