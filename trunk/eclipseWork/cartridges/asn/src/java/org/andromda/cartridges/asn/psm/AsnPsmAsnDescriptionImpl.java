//license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package org.andromda.cartridges.asn.psm;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import org.andromda.cartridges.asn.AsnUtils;
import org.andromda.metafacades.uml.AssociationEndFacade;
import org.andromda.metafacades.uml.AttributeFacade;
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
		Collection<AsnPsmElementDescription> blocks = new ArrayList<AsnPsmElementDescription>();
		this.setBlocks(blocks);
	}


	public void listAllKnownElements(Map<String, ModelElementFacade> blocks) {
		Iterator it = blocks.values().iterator();
		while(it.hasNext()) {
			ModelElementFacade m = (ModelElementFacade) it.next();
			debug("found Element: "+m.getFullyQualifiedName());
		}
	}

	/**
	 * @see org.andromda.cartridges.asn.psm.AsnPsmAsnDescription#buildFromClassifier(org.andromda.metafacades.uml.ClassifierFacade)
	 */
	@Override
	public boolean buildFromClassifier(ClassifierFacade classifier) {

		boolean result = super.buildFromClassifier(classifier);
		//AsnUtils.listAll(classifier);

		//collect all possible blocks
		//collectAllBlocks(classifier, blocks);
		//AsnUtils.listAll(classifier);
		//AsnUtils.listProperties(classifier);
		if (result == true) {
			Map<String, ModelElementFacade> blocks = new HashMap<String, ModelElementFacade>();
			result = buildElements(classifier, blocks);
			listAllKnownElements(blocks);
		}

		//get header from them
		return result;
	}




	/**
	 * //TODO What about abstract classes
	 * @param clFacade
	 * @param blocks
	 * @return
	 */
	public boolean buildElements(ModelElementFacade mFacade, Map<String, ModelElementFacade> blocks) {
		boolean result;
		if (blocks.containsKey(mFacade.getFullyQualifiedName())) {
			result = false;
		} else {
			error("build new ASN.1 Element from Model "+mFacade.getFullyQualifiedName());
			blocks.put(mFacade.getFullyQualifiedName(), mFacade);
			//go deeper
			if (mFacade instanceof ClassifierFacade) {
				ClassifierFacade cFacade = (ClassifierFacade) mFacade;
				Collection col = cFacade.getProperties(true);
				Iterator it = col.iterator();
				result = true;
				while(it.hasNext()){
					result = buildElements((ModelElementFacade)it.next(), blocks);
				}
			} else if (mFacade instanceof AssociationEndFacade) {
				AssociationEndFacade cFacade = (AssociationEndFacade) mFacade;
				/*
				Collection col = cFacade.
				Iterator it = col.iterator();
				*/
				result = true;
				//while(it.hasNext()){
				//	result = buildElements((ModelElementFacade)it.next(), blocks);
				//}
			} else if (mFacade instanceof AttributeFacade) {
				result = true;
			} else {
				error("unkown type: "+mFacade.toString());
				result = false;
			}
		}
		return result;
	}


	public void collectAllBlocks(ClassifierFacade clFacade, Map<String, ClassifierFacade> blocks) {
		if (!blocks.containsKey(clFacade.getFullyQualifiedName())) {
			error("found block"+clFacade.getFullyQualifiedName());
			blocks.put(clFacade.getFullyQualifiedName(), clFacade);
			Collection col = clFacade.getAllAssociatedClasses();
			Iterator it = col.iterator();
			while (it.hasNext()) {
				Object o = it.next();
				if (o instanceof ClassifierFacade) {
					collectAllBlocks((ClassifierFacade) o, blocks);
					//AsnUtils.listAll((ClassifierFacade) o);
				}
			}
		}
	}
}
