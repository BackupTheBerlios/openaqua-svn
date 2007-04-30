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
        return null;
    }

    /**
     * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacade#getFormatShortVersion()
     */
    protected java.lang.String handleGetFormatShortVersion()
    {
        // TODO: put your implementation here.
        return null;
    }

    /**
     * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacade#getHeader()
     */
    protected java.lang.Object handleGetHeader()
    {
        // TODO: add your implementation here!
        return null;
    }

    /**
     * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacade#getValues()
     */
    protected java.util.Collection handleGetValues()
    {
        // TODO: add your implementation here!
        return null;
    }

    /**
     * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionFacade#getFooter()
     */
    protected java.lang.Object handleGetFooter()
    {
        // TODO: add your implementation here!
        return null;
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