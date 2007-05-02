package org.andromda.cartridges.asn.metafacades;

import java.util.Collection;


/**
 * MetafacadeLogic implementation for org.andromda.cartridges.asn.metafacades.AsnSimpleDescriptionFacade.
 *
 * @see org.andromda.cartridges.asn.metafacades.AsnSimpleDescriptionFacade
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
		return false;
	}


	/* (non-Javadoc)
	 * @see org.andromda.cartridges.asn.metafacades.AsnSimpleDescriptionFacadeLogic#handleGetAsnDescription()
	 */
	@Override
	protected Collection handleGetAsnDescription() {
		// TODO Auto-generated method stub
		return null;
	}

}