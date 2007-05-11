//license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package org.andromda.cartridges.asn.psm;



/**
 * @see org.andromda.cartridges.asn.psm.AsnPsmElementDescription
 */
public abstract class Element
//extends org.andromda.cartridges.asn.psm.AsnPsmElementDescription
{
	public Element()
	{
		super();
	}

	public Element(java.lang.String type, java.lang.String shortName, java.lang.String fullName, java.lang.String documentation, java.lang.String range, boolean optional, boolean isAbstract)
	{
		//super(type, shortName, fullName, documentation, range, optional, isAbstract);
	}

	/**
	 * Copy-constructor from other AsnPsmElementDescription
	 *
	 * @param otherBean, cannot be <code>null</code>
	 * @throws java.lang.NullPointerException if the argument is <code>null</code>
	 */
	/*
	public Element(AsnPsmElementDescription otherBean)
	{
		this(otherBean.getType(), otherBean.getShortName(), otherBean.getFullName(), otherBean.getDocumentation(), otherBean.getRange(), otherBean.isOptional(), otherBean.isIsAbstract());
	}
	*/


	/*
	 * (non-Javadoc)
	 * @see org.andromda.cartridges.asn.psm.AsnPsmElementDescription#buildFromElementFacade(org.andromda.metafacades.uml.ModelElementFacade, java.util.Collection, java.util.Set)
	 * 
	 * allElements holds all object in the order of modeling!
	 * allNames holds the name of all known objects to make them unique - a Map doesn't work
	 */
	/*
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


		boolean result;
		
		//create substructure
    	if (element instanceof ClassifierFacade) {
    		ClassifierFacade cl = (ClassifierFacade) element;
    		this.isAbstract = cl.isAbstract();
        	result = true;
        	Collection col = cl.getAllProperties();
        	Iterator it = col.iterator();
        	while(it.hasNext()) {
        		//what is the variable name and what is the TypeName?
        		AsnPsmBlockDescription a = new AsnPsmBlockDescription();
        		a.buildFromElementFacade((ModelElementFacade) it.next(), allElements, allNames);
        		//getElements().add(a);
        	}
    	} else {
    		error("got unkown element type: " +element.toString());
    		result = false;
    	}
    	*/

		/*


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

		 */
	/*
		return result;
	}
	*/


}
