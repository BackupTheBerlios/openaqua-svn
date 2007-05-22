//license-header java merge-point
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
	public AsnPsmElement getAsnElement(ModelElementFacade element, Map knownElements, Integer level)  
	{
		//test for preexisting elements
		if (knownElements.containsKey(element.getFullyQualifiedName())) {
			AsnPsmElement e = (AsnPsmElement)knownElements.get(element.getFullyQualifiedName());
			debug("with preexisting Type: "+e.getType(), level);
			return e;
		}

		//otherwise create new elements
		if (element instanceof ClassifierFacade) {
			return getAsnElement((ClassifierFacade)element, knownElements, level);
		} else if (element instanceof AssociationEndFacade ) {
			return getAsnElement((AssociationEndFacade)element, knownElements, level);
		} else if (element instanceof AssociationClassFacade ) {
			return getAsnElement((AssociationClassFacade)element, knownElements, level);
		} else if (element instanceof AssociationFacade ) {
			return getAsnElement((AssociationFacade)element, knownElements, level);
		} else if (element instanceof AttributeFacade ) {
			return getAsnElement((AttributeFacade)element, knownElements, level);
		} else if (element instanceof AttributeLinkFacade ) {
			return getAsnElement((AttributeLinkFacade)element, knownElements, level);
		} else {
			String error="Unhandled ModelElementFacade: "+element.toString();
			throw new java.lang.UnsupportedOperationException(error);
		}
	}

	
	//get the applicationID tag
	private int getApplicationId(ModelElementFacade  element, Integer level) {
		int result = 0;
		
		//TODO replace strings by global constants
		Object tagged = element.findTaggedValue("applicationID");
		String applicationIDstr = (String) tagged;
		if (applicationIDstr!=null) {
			try {
				result = Integer.parseInt(applicationIDstr);
			} catch ( NumberFormatException e ) {
				result = 0;
			}
		}
		
		debug ("with Application ID="+result, level);
		return result;
	}


	private String getValueRange(ModelElementFacade  element, Integer level) {
		//TODO replace strings by global constants
		Object tagged = element.findTaggedValue("valueRange");
		String result = (String) tagged;
		if (result == null)
			result = "";
		
		debug ("with Range="+result, level);
		return result;
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
	private AsnPsmElement newAsnElement(ModelElementFacade  element, Map knownElements, Integer level)
	{
		final String datatype = dataTypeMapping(element.getFullyQualifiedName(), level);
		
		//return pre existing elements
		if (knownElements.containsKey(datatype)) {
			AsnPsmElement e = (AsnPsmElement)knownElements.get(element.getFullyQualifiedName());
			debug("with preexisting Type: "+e.getType(), level);
			return e;
			
		//or create a new one
		} else {
			debug ("with Type: "+datatype, level);

			//create a default Element
			AsnPsmElement result = new AsnPsmElement();
			result.setDocumentation(element.getDocumentation("-- "));
			result.setType(datatype); //like org.foo.bar.ClassName
			result.setName(element.getName());//like ClassName
			result.setSubElements(new ArrayList<AsnPsmNameElementPair>());
			result.setApplicationId(getApplicationId(element, level));
			result.setValueRange(getValueRange(element, level));


			knownElements.put(datatype, result);
			return result;
		}
	}



	/**
	 * @see org.andromda.cartridges.asn.psm.AsnPsmElementGenerator#getAsnElement(org.andromda.metafacades.uml.ClassifierFacade)
	 */
	@Override
	public AsnPsmElement getAsnElement(ClassifierFacade element, Map knownElements, Integer level)  
	{
		//check for pre existing elements
		//Warning: Removing this check will result in a unchecked recursive loop!
		final String datatype = dataTypeMapping(element.getFullyQualifiedName(), level); 
		if (knownElements.containsKey(datatype)) {
			AsnPsmElement e = (AsnPsmElement)knownElements.get(element.getFullyQualifiedName());
			debug("with preexisting Type: "+e.getType(), level);
			return e;
		} 

		//create a default Element
		AsnPsmElement result = newAsnElement(element, knownElements, level);
		
		//add subElements
		debug ("with subElements: ", level);
		@SuppressWarnings("unchecked")
		Collection<AsnPsmNameElementPair> subElements = result.getSubElements();
		Collection col = element.getAllProperties();
		Iterator it = col.iterator();
		int countSubElements=1; //counts the elements, just for nice debug output
		while(it.hasNext()){
			//get the sub element facade
			ModelElementFacade m = (ModelElementFacade) it.next();
			final String name = m.getFullyQualifiedName();

			//make a debug output
			debug("Element No "+countSubElements++ + " with Name: "+name, level+1);
			final int subLevel=level+2;

			//build the subElement
			AsnPsmElement subElement = getAsnElement(m, knownElements, subLevel);
			
			//store the subElement
			if (subElement != null) {
				AsnPsmNameElementPair pair = new AsnPsmNameElementPair();
				pair.setName(m.getName());
				pair.setElement(subElement);
				subElements.add(pair);
			}
		}
		
		//store all subElements
		result.setSubElements(subElements);

		//return the created Element
		return result;
	}

	
	
	
	/**
	 * @see org.andromda.cartridges.asn.psm.AsnPsmElementGenerator#getAsnElement(org.andromda.metafacades.uml.AssociationEndFacade)
	 */
	@Override
	public AsnPsmElement getAsnElement(AssociationEndFacade element, Map knownElements, Integer level)
	{
		return getAsnElement(element.getType(), knownElements, level);
	}

	
	
	/* (non-Javadoc)
	 * @see org.andromda.cartridges.asn.psm.AsnPsmElementGenerator#getAsnElement(org.andromda.metafacades.uml.AssociationFacade)
	 */
	@Override
	public AsnPsmElement getAsnElement(AssociationFacade element, Map knownElements, Integer level) 
	{
		error("getAsnElement(AssociationFacade element)  not finished");
		return null;
	}

	
	
	/* (non-Javadoc)
	 * @see org.andromda.cartridges.asn.psm.AsnPsmElementGenerator#getAsnElement(org.andromda.metafacades.uml.AssociationClassFacade)
	 */
	@Override
	public AsnPsmElement getAsnElement(AssociationClassFacade element, Map knownElements, Integer level) 
	{
		error("getAsnElement(AssociationClassFacade element)  not finished");
		return null;
	}

	
	
	/* (non-Javadoc)
	 * @see org.andromda.cartridges.asn.psm.AsnPsmElementGenerator#getAsnElement(org.andromda.metafacades.uml.AttributeFacade)
	 */
	@Override
	public AsnPsmElement getAsnElement(AttributeFacade element, Map knownElements, Integer level) 
	{
		return getAsnElement(element.getType(), knownElements, level);
	}


	
	
	/* (non-Javadoc)
	 * @see org.andromda.cartridges.asn.psm.AsnPsmElementGenerator#getAsnElement(org.andromda.metafacades.uml.AttributeLinkFacade)
	 */
	@Override
	public AsnPsmElement getAsnElement(AttributeLinkFacade element, Map knownElements, Integer Level) 
	{
		error("getAsnElement(AttributeLinkFacade element)  not finished");
		return null;
	}

	
	
	/* (non-Javadoc)
	 * @see org.andromda.cartridges.asn.psm.AsnPsmElementGenerator#dataTypeMapping(java.lang.String)
	 */
	@Override
	public String dataTypeMapping(String original, Integer Level) {
		if (original.toUpperCase().equals("java.lang.String")) return "VisibleString";

		if (original.toUpperCase().equals("boolean")) return "BOOLEAN";
		if (original.toUpperCase().equals("java.lang.boolean")) return "BOOLEAN";

		if (original.toUpperCase().equals("int")) return "INTEGER";
		if (original.toUpperCase().equals("integer")) return "INTEGER";
		if (original.toUpperCase().equals("java.lang.integer")) return "INTEGER";
		if (original.toUpperCase().equals("long")) return "INTEGER";
		if (original.toUpperCase().equals("java.lang.long")) return "INTEGER";

		if (original.toUpperCase().equals("java.lang.double")) return "NUMBER";
		if (original.toUpperCase().equals("java.lang.float")) return "NUMBER";
		if (original.toUpperCase().equals("double")) return "NUMBER";
		if (original.toUpperCase().equals("float")) return "NUMBER";

		return original;
	}

}
