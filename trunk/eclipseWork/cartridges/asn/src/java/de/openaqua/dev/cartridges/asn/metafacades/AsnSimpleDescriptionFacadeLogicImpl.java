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
    //extends AsnSimpleDescriptionFacadeLogic
{
	/*
	final Logger logger = Logger.getRootLogger();
    public AsnSimpleDescriptionFacadeLogicImpl (Object metaObject, String context)
    {
        super (metaObject, context);
    }
    */

    
/*
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


	
	protected Collection handleGetDetailDescription() {
		Context context = new Context();
		context.stereotype = "ValueObject";
		getAllBlocksWithStereotypeRecursive(this, context);
		return context.values;
	}

	
	
	protected Collection handleGetFooterDescription() {
		return getAllBlocksWithStereotype("AsnSimpleFooter");
	}

	
	
	protected Collection handleGetHeaderDescription() {
		return getAllBlocksWithStereotype("AsnSimpleHeader");
	}

	
	
	protected boolean handleHasDetailDescription() {
		return hasAssocWithCertainStereotype("ValueObject");
	}

	
	
	protected boolean handleHasFooterDescription() {
		return hasAssocWithCertainStereotype("AsnSimpleFooter");
	}
	
	

	protected boolean handleHasHeaderDescription() {
		return hasAssocWithCertainStereotype("AsnSimpleHeader");
	}

*/
}