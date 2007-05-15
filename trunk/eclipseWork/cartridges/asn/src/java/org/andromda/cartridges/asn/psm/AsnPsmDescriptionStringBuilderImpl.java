// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package org.andromda.cartridges.asn.psm;

import java.util.Collection;
import java.util.Iterator;

/**
 * @see org.andromda.cartridges.asn.psm.AsnPsmDescriptionStringBuilder
 */
public class AsnPsmDescriptionStringBuilderImpl
    extends org.andromda.cartridges.asn.psm.AsnPsmDescriptionStringBuilder
{
	final String COMMENTLINE="-- ------------------------------------\n";
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
        String result = "";
        result += getFileHeader(description);
        result += getFileBody(description);
        result += getFileTrailer(description);
        return result;
    }
    
    private String getFileHeader(final AsnPsmAsnDescription description) {
    	String result = 
    		"-- This is a generated file, dont modify it manually\n"+
    		COMMENTLINE+
    		"-- SYNTAX PRODUCED BY: AndroMDA ASN.1 Cartridge\n"+
    		"-- SYNTAX LOCATION AT: "+description.getPackageName()+".asn\n"+
    		" \n"+
    		" \n"+
    		" \n";
    	if (description.getDocumenation().length()>3) {
    		result += COMMENTLINE;
    		result += description.getDocumenation();
    		result += COMMENTLINE;
    	}
    	result+=description.getName() + " DEFINITIONS IMPLICIT TAGS ::=\n\n";
    	result+="BEGIN\n\n ";
    	return result;
    }

    private String getFileBody(final AsnPsmAsnDescription description) {
    	String result ="\n";
    	
    	Iterator it = description.getAllElements().iterator();
    	while(it.hasNext()) {
    		AsnPsmElement element = (AsnPsmElement) it.next();
    		if (element.getDocumentation().length()>3) {
    			result += "\n"+COMMENTLINE+element.getDocumentation()+COMMENTLINE;
    		}
    		if (element.isPrimitive() == false) {
    			result +=element.getName()+ " ::= SEQUENCE \n";
    			result +="{\n";
    			Iterator subs = element.getSubElements().iterator();
    			while(subs.hasNext()) {
    				AsnPsmNameElementPair pair = (AsnPsmNameElementPair) subs.next();
    				result += "\t"+pair.getName()+"\t\t"+pair.getElement().getType();
    				if (subs.hasNext()) result+=",";
    				result +="\n";
    			}
    			result +="}\n \n \n";
    		} else {
    			result +=element.getName()+ "\n";
    		}
    		//if (element.getApplicationId()>0) {
    		//	result+="[APPLICATION "+element.getApplicationId()+"] ";    			
    		//}
    		//result += element.getType();
    		//result +="\n";
    	}
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
