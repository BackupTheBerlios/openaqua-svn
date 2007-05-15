// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package org.andromda.cartridges.asn.psm;

/**
 * @see org.andromda.cartridges.asn.psm.AsnPsmDescriptionStringBuilder
 */
public class AsnPsmDescriptionStringBuilderImpl
    extends org.andromda.cartridges.asn.psm.AsnPsmDescriptionStringBuilder
{
    public AsnPsmDescriptionStringBuilderImpl()
    {
        super();
    }

    /**
     * Copy-constructor from other AsnPsmDescriptionStringBuilder
     *
     * @param otherBean, cannot be <code>null</code>
     * @throws java.lang.NullPointerException if the argument is <code>null</code>
     */
    public AsnPsmDescriptionStringBuilderImpl(AsnPsmDescriptionStringBuilder otherBean)
    {
        this();
    }

    /**
     * @see org.andromda.cartridges.asn.psm.AsnPsmDescriptionStringBuilder#getString(org.andromda.cartridges.asn.psm.AsnPsmAsnDescription)
     */
    public java.lang.String getString(AsnPsmAsnDescription description)
    {
        String result = getFileHeader(description);
        result += getFileTrailer(description);
        return result;
    }
    
    private String getFileHeader(final AsnPsmAsnDescription description) {
    	String result = 
    		"-- This is a generated file, dont modify it manually\n"+
    		"-- ------------------------------------------------------\n"+
    		"-- SYNTAX PRODUCED BY: AndroMDA ASN.1 Cartridge\n"+
    		"-- SYNTAX LOCATION AT: "+description.getPackageName()+".asn\n"+
    		" \n"+
    		" \n"+
    		" \n"
    		;

    	return result;
    }

    private String getFileTrailer(final AsnPsmAsnDescription description) {
    	String result =
    		" \n"+
    		" \n"+
    		" \n"+
    		"-- --------------------------------------\n" +
    		"END\n"
    		;

    	return result;
    }
}
