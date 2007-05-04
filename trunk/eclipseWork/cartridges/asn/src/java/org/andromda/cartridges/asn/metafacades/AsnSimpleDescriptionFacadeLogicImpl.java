package org.andromda.cartridges.asn.metafacades;

import java.util.ArrayList;
import java.util.Collection;

import org.andromda.cartridges.asn.psm.AsnPsmAsnDescription;
import org.andromda.cartridges.asn.psm.AsnPsmAsnDescriptionImpl;
import org.apache.log4j.Logger;


/**
 * MetafacadeLogic implementation for org.andromda.cartridges.asn.metafacades.AsnSimpleDescriptionFacade.
 *
 * @see org.andromda.cartridges.asn.metafacades.AsnSimpleDescriptionFacade
 */
public class AsnSimpleDescriptionFacadeLogicImpl
    extends AsnSimpleDescriptionFacadeLogic
{
	final Logger logger = Logger.getRootLogger();
    public AsnSimpleDescriptionFacadeLogicImpl (Object metaObject, String context)
    {
        super (metaObject, context);
        logger.info("Instanciate ASN.1 Facade");
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
		AsnPsmAsnDescription desc = new AsnPsmAsnDescriptionImpl();
		Collection<AsnPsmAsnDescription> result = new ArrayList<AsnPsmAsnDescription>();
		result.add(desc);
		return result;
	}

}