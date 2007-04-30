package de.openaqua.dev.cartridges.asn.metafacades;



/**
 * MetafacadeLogic implementation for de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacade.
 *
 * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacade
 */
public class AsnSimpleDescriptionFacadeLogicImpl
    extends AsnSimpleDescriptionFacadeLogic
{

	public String myTest;
    public AsnSimpleDescriptionFacadeLogicImpl (Object metaObject, String context)
    {
        super (metaObject, context);
        myTest="fooo";
    }

    /**
     * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacade#getFormatShortName()
     */
    protected java.lang.String handleGetFormatShortName()
    {
        // TODO: put your implementation here.
        return "handleGetFormatShortName";
    }

    /**
     * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacade#getFormatShortVersion()
     */
    protected java.lang.String handleGetFormatShortVersion()
    {
        // TODO: put your implementation here.
        return "handleGetFormatShortVersion";
    }


	/* (non-Javadoc)
	 * @see org.andromda.metafacades.uml.ClassifierFacade#isEmbeddedValue()
	 */
	public boolean isEmbeddedValue() {
		// TODO Auto-generated method stub
		return false;
	}

	/* (non-Javadoc)
	 * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacadeLogic#handleGetDescriptionImplementationName()
	 */
	@Override
	protected String handleGetDescriptionImplementationName() {
		// TODO Auto-generated method stub
		return "handleGetDescriptionImplementationName";
	}

	/* (non-Javadoc)
	 * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacadeLogic#handleGetDescriptionName()
	 */
	@Override
	protected String handleGetDescriptionName() {
		// TODO Auto-generated method stub
		return "handleGetDescriptionName";
	}

}