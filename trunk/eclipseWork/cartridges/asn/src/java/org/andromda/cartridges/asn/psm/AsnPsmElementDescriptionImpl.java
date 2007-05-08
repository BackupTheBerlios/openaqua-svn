//license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package org.andromda.cartridges.asn.psm;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

import org.andromda.cartridges.asn.AsnUtils;
import org.andromda.metafacades.emf.uml2.AssociationEndFacadeLogicImpl;
import org.andromda.metafacades.uml.AssociationEndFacade;
import org.andromda.metafacades.uml.AttributeFacade;
import org.andromda.metafacades.uml.ClassifierFacade;
import org.andromda.metafacades.uml.ModelElementFacade;


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

	public AsnPsmElementDescriptionImpl(java.lang.String type, java.lang.String shortName, java.lang.String fullName, java.lang.String documentation, java.lang.String range, boolean optional, boolean isAbstract)
	{
		super(type, shortName, fullName, documentation, range, optional, isAbstract);
	}

	/**
	 * Copy-constructor from other AsnPsmElementDescription
	 *
	 * @param otherBean, cannot be <code>null</code>
	 * @throws java.lang.NullPointerException if the argument is <code>null</code>
	 */
	public AsnPsmElementDescriptionImpl(AsnPsmElementDescription otherBean)
	{
		this(otherBean.getType(), otherBean.getShortName(), otherBean.getFullName(), otherBean.getDocumentation(), otherBean.getRange(), otherBean.isOptional(), otherBean.isIsAbstract());
	}


	@Override
    public boolean buildFromElementFacade(org.andromda.metafacades.uml.ModelElementFacade element, java.util.Collection allElements, java.util.Set allNames) {
		if (element == null){
			error("got null reference as classifier");
			return false;
		} 
		
		if (allNames.contains(element.getFullyQualifiedName())) {
			return true;			
		} 
		
		allNames.add(element.getFullyQualifiedName());
		allElements.add(this);
		info("Got ElementType "+element.getFullyQualifiedName());

		
		//create my self
		this.setFullName(element.getFullyQualifiedName().replaceAll("\\.", "/"));
		this.setShortName(element.getName());
		this.setDocumentation(element.getDocumentation("-- "));
		this.isAbstract = false;
		
		
		//create substructure

		/*

        	if (element instanceof ClassifierFacade) {
        		ClassifierFacade cl = (ClassifierFacade) element;
        		this.isAbstract = cl.isAbstract();
            	result = true;
            	Collection col = cl.getAllProperties();
            	Iterator it = col.iterator();
            	while(it.hasNext()) {
            		AsnPsmBlockDescription a = new AsnPsmBlockDescription();
            		a.buildFromElementFacade((ModelElementFacade) it.next(), allElements);
            	}

        	} else if (element instanceof AssociationEndFacade) {
        		this.isAbstract = false;

        		AssociationEndFacade end = (AssociationEndFacade) element;
        		ClassifierFacade other = end.getOtherEnd().getAssociation().getAssociationEndB().getType();
        		AsnPsmBlockDescription a = new AsnPsmBlockDescription();
        		result = a.buildFromElementFacade(other, allElements);

        	} else if (element instanceof AttributeFacade) {
        		//AttributeFacade at = (AttributeFacade) element;
        		this.isAbstract = false;
            	result = true;

        	} else {
        		error("got unkown element type: " +element.toString());
        		result = false;
        	}
		 */
		return true;
	}


}
