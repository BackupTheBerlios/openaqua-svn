/**
 * 
 */
package org.andromda.cartridges.asn;

import java.util.Collection;
import java.util.Iterator;
import java.util.List;

import org.andromda.cartridges.asn.psm.AsnLogger;
import org.andromda.cartridges.asn.psm.AsnLoggerImpl;
import org.andromda.metafacades.emf.uml2.AssociationEndFacadeLogicImpl;
import org.andromda.metafacades.emf.uml2.AttributeFacadeLogicImpl;
import org.andromda.metafacades.uml.AssociationEndFacade;
import org.andromda.metafacades.uml.ClassifierFacade;

/**
 * @author behrenan
 *
 */
public class AsnUtils {
	static AsnLogger logger = new AsnLoggerImpl();


	static private void ListSomething(final String header, final String element, final Collection coll) {
		logger.warn(header);
		Iterator it = coll.iterator();
		while (it.hasNext()) {
			Object o = it.next();
			if (o instanceof ClassifierFacade) {
				ClassifierFacade c = (ClassifierFacade) o; 
				logger.error("\t" + element + "\t" + c.getName());
			}else if (o instanceof AttributeFacadeLogicImpl) {
				AttributeFacadeLogicImpl c = (AttributeFacadeLogicImpl) o; 
				logger.error("\t" + element + "\t" + c.getName());
			}else if (o instanceof AssociationEndFacadeLogicImpl) {
				AssociationEndFacadeLogicImpl c = (AssociationEndFacadeLogicImpl) o; 
				logger.error("\t" + element + "\t" + c.getName());
			}else  {
				logger.error("unkown type: "+o.toString());
			}
		}
	}

	static public void listProperties(org.andromda.metafacades.uml.ClassifierFacade classifier) {
		ListSomething("List Properties", "property", classifier.getProperties(true));
	}

	static public void listAttributes(org.andromda.metafacades.uml.ClassifierFacade classifier) {
		ListSomething("List Attributes", "attributes", classifier.getAttributes());
	}

	static public void listSAttributes(org.andromda.metafacades.uml.ClassifierFacade classifier) {
		ListSomething("List SAttributes", "sattributes", classifier.getStaticAttributes());
	}

	static public void listIAttributes(org.andromda.metafacades.uml.ClassifierFacade classifier) {
		ListSomething("List IAttributes", "iattributes", classifier.getInstanceAttributes());
	}

	static public void listAllAssociatedClasses(org.andromda.metafacades.uml.ClassifierFacade classifier) {
		ListSomething("List getAllAssociatedClasses", "assoc", classifier.getAllAssociatedClasses());
	}

	static public void listAssociationEnds(org.andromda.metafacades.uml.ClassifierFacade classifier) {
		ListSomething("List getAssociationEnds", "ends", classifier.getAssociationEnds());
	}
	
	static public void listNavigableConnectingEnds(org.andromda.metafacades.uml.ClassifierFacade classifier) {
		ListSomething("List getNavigableConnectingEnds", "navis", classifier.getNavigableConnectingEnds());
	}

	
	static public void listAll(org.andromda.metafacades.uml.AssociationEndFacade classifier) {
		logger.error("dump Content for: "+classifier.getFullyQualifiedName());
		//org.andromda.metafacades.uml.AssociationFacade otherAssoc = classifier.getOtherEnd().getAssociation();
		ClassifierFacade other = classifier.getOtherEnd().getAssociation().getAssociationEndB().getType();
		logger.error("other: "+other.getFullyQualifiedName());
		List l = classifier.getOtherEnd().getAssociation().getAssociationEnds();
		Iterator it = l.iterator();
		while(it.hasNext()) {
			AssociationEndFacade end = (AssociationEndFacade) it.next();
			ClassifierFacade attach = end.getType();
			logger.error("end: "+attach.getFullyQualifiedName());
			//logger.error("other Ends: "+it.next().toString());
			
		}
		
	}
	
	static public void listAll(org.andromda.metafacades.uml.ClassifierFacade classifier) {
		logger.error("dump Content for: "+classifier.getFullyQualifiedName());
		ListSomething("getAbstractions()", "a", classifier.getAbstractions() );
		ListSomething("getAllAssociatedClasses() ", "a", classifier.getAllAssociatedClasses() );
		ListSomething("getAllProperties() ", "a", classifier.getAllProperties() );
		ListSomething("getAllRequiredConstructorParameters() ", "a", classifier.getAllRequiredConstructorParameters() );
		ListSomething("getAssociatedClasses() ", "a", classifier.getAssociatedClasses() );
		ListSomething("getAssociationEnds() ", "a", classifier.getAssociationEnds() );
		ListSomething("getAttributes() ", "a", classifier.getAttributes() );
		ListSomething("getAttributes(true)", "a", classifier.getAttributes(true));
		ListSomething("getAttributes(false)", "a", classifier.getAttributes(false));
		ListSomething("getImplementationOperations() ", "a", classifier.getImplementationOperations() );
		ListSomething("getNavigableConnectingEnds() ", "a", classifier.getNavigableConnectingEnds()  );
		ListSomething("getInstanceAttributes() ", "a", classifier.getInstanceAttributes() );
		ListSomething("getInstanceOperations() ", "a", classifier.getInstanceOperations() );
		ListSomething("getInterfaceAbstractions() ", "a", classifier.getInterfaceAbstractions() );
		ListSomething("getNavigableConnectingEnds(true)", "a", classifier.getNavigableConnectingEnds(true) );
		ListSomething("getNavigableConnectingEnds(false)", "a", classifier.getNavigableConnectingEnds(false));
		ListSomething("getOperations() ", "a", classifier.getOperations() );
		ListSomething("getProperties() ", "a", classifier.getProperties() );
		ListSomething("getProperties(true) ", "a", classifier.getProperties(true) );
		ListSomething("getProperties(false) ", "a", classifier.getProperties(false) );
		ListSomething("getRequiredConstructorParameters() ", "a", classifier.getRequiredConstructorParameters() );
		ListSomething("getStaticAttributes() ", "a", classifier.getStaticAttributes() );
		ListSomething("getStaticOperations() ", "a", classifier.getStaticOperations() );
	}

}
