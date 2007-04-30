package de.openaqua.dev.cartridges.asn.metafacades;


/**
 * MetafacadeLogic implementation for de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleObjectFacade.
 *
 * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleObjectFacade
 */
public class AsnSimpleObjectFacadeLogicImpl
    extends AsnSimpleObjectFacadeLogic
{

    public AsnSimpleObjectFacadeLogicImpl (Object metaObject, String context)
    {
        super (metaObject, context);
    }

    /**
     * @see de.openaqua.dev.cartridges.asn.metafacades.AsnSimpleObjectFacade#getAsnApplicationId()
     */
    protected int handleGetAsnApplicationId()
    {
        // TODO: put your implementation here.
        return 0;
    }

	/* (non-Javadoc)
	 * @see org.andromda.metafacades.uml.ClassifierFacade#isEmbeddedValue()
	 */
	public boolean isEmbeddedValue() {
		// TODO Auto-generated method stub
		return false;
	}

}