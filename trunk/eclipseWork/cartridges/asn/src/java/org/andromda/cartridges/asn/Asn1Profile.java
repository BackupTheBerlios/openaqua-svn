/**
 * 
 */
package org.andromda.cartridges.asn;


import org.andromda.core.profile.Profile;
import org.andromda.metafacades.uml.UMLProfile;

/**
 *
 */
public class Asn1Profile 
    extends UMLProfile {

    /**
     * The Profile instance from which we retrieve the mapped profile names.
     */
    private static final Profile profile = Profile.instance();

    public static final String STEREOTYPE_ASN_DESCRIPTION = profile.get("ASN_DESCRIPTION");

}
