package de.openaqua.dev.cartridges.asn.metafacades;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

import org.andromda.metafacades.emf.uml2.ClassifierFacadeLogicImpl;
import org.andromda.metafacades.uml.ClassifierFacade;
import org.apache.log4j.Logger;



/**
 * MetafacadeLogic implementation for de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacade.
 *
 * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacade
 */
public class AsnSimpleDescriptionFacadeLogicImpl
    extends AsnSimpleDescriptionFacadeLogic
{
	final Logger logger = Logger.getRootLogger();
    public AsnSimpleDescriptionFacadeLogicImpl (Object metaObject, String context)
    {
        super (metaObject, context);
    }

    
	/* (non-Javadoc)
	 * @see org.andromda.metafacades.uml.ClassifierFacade#isEmbeddedValue()
	 */
	public boolean isEmbeddedValue() {
		return false;
	}

	private boolean hasAssocWithCertainStereotype(final String stereotype){
		Iterator it = getAllAssociatedClasses().iterator();
		while(it.hasNext()) {
			Object o = it.next();
			if (o instanceof ClassifierFacadeLogicImpl){
				ClassifierFacadeLogicImpl c = (ClassifierFacadeLogicImpl)o;
				if (true == c.hasExactStereotype(stereotype)) {
					return true;
				}
			}
		}
		
		return false;
		
	}


	/**
	 * 
	 * @param stereotype
	 * @return
	 */
	private Collection getAllBlocksWithStereotype(final String stereotype) {
		Collection<ClassifierFacade> result = new ArrayList<ClassifierFacade>();
		Iterator it = getAllAssociatedClasses().iterator();
		while(it.hasNext()) {
			Object o = it.next();
			if (o instanceof ClassifierFacadeLogicImpl){
				ClassifierFacadeLogicImpl c = (ClassifierFacadeLogicImpl)o;
				if (true == c.hasExactStereotype(stereotype)) {
					result.add(c);
				}
			}
		}
		return result;
	}

	/**
	 * This Context object will be used like a Map. But the values must be 
	 * stored in a predefined order!
	 * 
	 */
	private class Context {
		public String stereotype;
		public Collection<ClassifierFacade> values;
		public Set<String> keys;
		public Context() {
			stereotype = "";
			values = new ArrayList<ClassifierFacade>();
			keys = new HashSet<String>();
		}
	}
	
	/**
	 * @todo Bug: ValueObjekte mit identischem Namen in unterschiedlichen pfaden
	 * @param classifier
	 * @param stereotype
	 * @param result
	 */
	private void getAllBlocksWithStereotypeRecursive(
			final ClassifierFacade classifier, 
			Context context) 
	{
		Iterator it = classifier.getAllAssociatedClasses().iterator();
		while(it.hasNext()) {
			Object o = it.next();
			if (o instanceof ClassifierFacade){
				ClassifierFacade c = (ClassifierFacade)o;
				if (c.hasStereotype(context.stereotype) 
						&&	!context.keys.contains(c.getFullyQualifiedName())) 
				{
					context.keys.add(c.getFullyQualifiedName());
					context.values.add(c);
					getAllBlocksWithStereotypeRecursive(c, context);
				}
			}
		}
	}


	
	/* (non-Javadoc)
	 * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacadeLogic#handleGetDetailDescription()
	 */
	@Override
	protected Collection handleGetDetailDescription() {
		Context context = new Context();
		context.stereotype = "ValueObject";
		getAllBlocksWithStereotypeRecursive(this, context);
		return context.values;
	}

	
	
	/* (non-Javadoc)
	 * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacadeLogic#handleGetFooterDescription()
	 */
	@Override
	protected Collection handleGetFooterDescription() {
		return getAllBlocksWithStereotype("AsnSimpleFooter");
	}

	
	
	/* (non-Javadoc)
	 * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacadeLogic#handleGetHeaderDescription()
	 */
	@Override
	protected Collection handleGetHeaderDescription() {
		return getAllBlocksWithStereotype("AsnSimpleHeader");
	}

	
	
	/* (non-Javadoc)
	 * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacadeLogic#handleHasDetailDescriptions()
	 */
	@Override
	protected boolean handleHasDetailDescription() {
		return hasAssocWithCertainStereotype("ValueObject");
	}

	
	
	/* (non-Javadoc)
	 * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacadeLogic#handleHasFooterDescription()
	 */
	@Override
	protected boolean handleHasFooterDescription() {
		return hasAssocWithCertainStereotype("AsnSimpleFooter");
	}
	
	

	/* (non-Javadoc)
	 * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacadeLogic#handleHasHeaderDescription()
	 */
	@Override
	protected boolean handleHasHeaderDescription() {
		return hasAssocWithCertainStereotype("AsnSimpleHeader");
	}


}