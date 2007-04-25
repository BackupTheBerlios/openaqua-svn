package de.openaqua.dev.cartridges.asn.metafacades;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

import org.andromda.metafacades.uml.ClassifierFacade;
import org.andromda.metafacades.uml.DependencyFacade;
import org.andromda.metafacades.uml.ModelElementFacade;

import de.openaqua.dev.cartridges.asn.psm.Description;



/**
 * MetafacadeLogic implementation for de.openaqua.dev.cartridges.asn.metafacades.AsnFacade.
 *
 * @see de.openaqua.dev.cartridges.asn.metafacades.AsnFacade
 */
public class AsnFacadeLogicImpl
    extends AsnFacadeLogic
{

    public AsnFacadeLogicImpl (Object metaObject, String context)
    {
        super (metaObject, context);
        
        
    }
    /**
     * @see de.openaqua.dev.cartridges.asn.metafacades.AsnFacade#getAsnSimpleDescriptions()
     */
    protected java.util.Collection handleGetAsnSimpleDescriptions()
    {
    	
    	System.out.println("aaaaaaaaaaaaaaaaaaaaoooooooooooooooooooooooo");
    	Collection result = new ArrayList();

    	Collection sourceDependencies = this.getSourceDependencies();
        for (Iterator iter = sourceDependencies.iterator(); iter.hasNext();)
        {
            DependencyFacade element = (DependencyFacade) iter.next();
        	System.out.println("aaaaaaaaaaaaaaaaaaaaa"+element.getFullyQualifiedName());
            ModelElementFacade targetElement = element.getTargetElement();
            if (targetElement instanceof ClassifierFacade)
            {
            	System.out.println("bbbb");

            	ClassifierFacade otherClass = (ClassifierFacade) targetElement;
            	Description description = new Description();
            	description.setDescription("otherClass.getFullyQualifiedNamePath()="+otherClass.getFullyQualifiedNamePath());
            	result.add(description);
            }
        }
        return result;
    }

}