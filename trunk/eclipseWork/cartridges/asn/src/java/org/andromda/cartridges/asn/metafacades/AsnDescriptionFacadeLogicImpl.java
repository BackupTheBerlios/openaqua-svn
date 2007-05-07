package org.andromda.cartridges.asn.metafacades;

import org.andromda.cartridges.asn.psm.AsnLogger;
import org.andromda.cartridges.asn.psm.AsnLoggerImpl;
import org.andromda.cartridges.asn.psm.AsnPsmAsnDescription;
import org.andromda.cartridges.asn.psm.AsnPsmAsnDescriptionImpl;


/**
 * MetafacadeLogic implementation for org.andromda.cartridges.asn.metafacades.AsnDescriptionFacade.
 *
 * @see org.andromda.cartridges.asn.metafacades.AsnDescriptionFacade
 */
public class AsnDescriptionFacadeLogicImpl
    extends AsnDescriptionFacadeLogic
{
	private final AsnLogger logger = new AsnLoggerImpl();

    public AsnDescriptionFacadeLogicImpl (Object metaObject, String context)
    {
        super (metaObject, context);
        logger.info("Instanciate ASN.1 Facade");
    }
    /**
     * @see org.andromda.cartridges.asn.metafacades.AsnDescriptionFacade#getAsnDescription()
     */
    protected org.andromda.cartridges.asn.psm.AsnPsmAsnDescription handleGetAsnDescription()
    {
		AsnPsmAsnDescription desc = new AsnPsmAsnDescriptionImpl();
		desc.buildFromClassifier(this);
		return desc;
    }

}