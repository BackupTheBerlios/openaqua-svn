package de.openaqua.dev.cartridges.asn.metafacades;

import java.util.Iterator;

import org.andromda.metafacades.emf.uml2.ClassifierFacadeLogicImpl;



/**
 * MetafacadeLogic implementation for de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacade.
 *
 * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacade
 */
public class AsnSimpleDescriptionFacadeLogicImpl
    extends AsnSimpleDescriptionFacadeLogic
{
    public AsnSimpleDescriptionFacadeLogicImpl (Object metaObject, String context)
    {
        super (metaObject, context);
    }

	/* (non-Javadoc)
	 * @see org.andromda.metafacades.uml.ClassifierFacade#isEmbeddedValue()
	 */
	public boolean isEmbeddedValue() {
		// TODO Auto-generated method stub
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
	
	/* (non-Javadoc)
	 * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacadeLogic#handleIsHasDetailRecords()
	 */
	@Override
	protected boolean handleIsHasDetailRecords() {
		return hasAssocWithCertainStereotype("AsnStorable");
	}

	/* (non-Javadoc)
	 * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacadeLogic#handleIsHasFooterRecord()
	 */
	@Override
	protected boolean handleIsHasFooterRecord() {
		return hasAssocWithCertainStereotype("AsnSimpleFooter");
	}

	/* (non-Javadoc)
	 * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacadeLogic#handleIsHasHeaderRecord()
	 */
	@Override
	protected boolean handleIsHasHeaderRecord() {
		return hasAssocWithCertainStereotype("AsnSimpleHeader");
	}

}