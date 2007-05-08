//license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package org.andromda.cartridges.asn.psm;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import org.andromda.metafacades.uml.ClassifierFacade;
import org.andromda.metafacades.uml.ModelElementFacade;

/**
 * @see org.andromda.cartridges.asn.psm.AsnPsmAsnDescription
 */
public class AsnPsmAsnDescriptionImpl
extends org.andromda.cartridges.asn.psm.AsnPsmAsnDescription
{
	public AsnPsmAsnDescriptionImpl()
	{
		super();
		Collection<AsnPsmElementDescription> allElements = new ArrayList<AsnPsmElementDescription>();
		this.setAllElements(allElements);
		this.allKeys = new HashSet<String>();
	}

	/* (non-Javadoc)
	 * @see org.andromda.cartridges.asn.psm.AsnPsmAsnDescription#buildFromClassifierFacade(org.andromda.metafacades.uml.ClassifierFacade)
	 */
	@Override
	public boolean buildFromClassifierFacade(ClassifierFacade classifier) {
		return buildFromElementFacade(classifier, getAllElements(), getAllKeys());
	}


	/* (non-Javadoc)
	 * @see org.andromda.cartridges.asn.psm.AsnPsmElementDescription#buildFromElementFacade(org.andromda.metafacades.uml.ModelElementFacade, java.util.Collection, java.util.Set)
	 */
	@Override
	public boolean buildFromElementFacade(ModelElementFacade element, Collection allElements, Set allNames) {
		return super.buildFromElementFacade(element, allElements, allKeys);
	}
}
