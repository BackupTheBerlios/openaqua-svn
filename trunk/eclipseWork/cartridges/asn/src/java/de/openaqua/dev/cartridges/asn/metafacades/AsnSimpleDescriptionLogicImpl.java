package de.openaqua.dev.cartridges.asn.metafacades;

import java.util.Collection;


/**
 * MetafacadeLogic implementation for de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescription.
 *
 * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescription
 */
public class AsnSimpleDescriptionLogicImpl
    extends AsnSimpleDescriptionLogic
{
    String myTest;

    public AsnSimpleDescriptionLogicImpl (Object metaObject, String context)
    {
        super (metaObject, context);
        myTest="fooo";
    }

    /**
     * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescription#getFormatShortName()
     */
    protected java.lang.String handleGetFormatShortName()
    {
    	return "ShortNameDefault";
    }

    /**
     * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescription#getFormatShortVersion()
     */
    protected java.lang.String handleGetFormatShortVersion()
    {
    	return "ShortVersioDefault";
    }

	/* (non-Javadoc)
	 * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionLogic#handleGetFooter()
	 */
	@Override
	protected Object handleGetFooter() {
		// TODO Auto-generated method stub
		return null;
	}

	/* (non-Javadoc)
	 * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionLogic#handleGetHeader()
	 */
	@Override
	protected Object handleGetHeader() {
		// TODO Auto-generated method stub
		return null;
	}

	/* (non-Javadoc)
	 * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleDescriptionLogic#handleGetValues()
	 */
	@Override
	protected Collection handleGetValues() {
		// TODO Auto-generated method stub
		return null;
	}
	public boolean isEmbeddedValue() {
		// TODO Auto-generated method stub
		return false;
	}

}