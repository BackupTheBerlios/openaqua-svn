/**
 * 
 */
package org.andromda.cartridges.asn.psm;


/**
 * @author behrenan
 *
 */
public class AsnPsmBlockDescriptionImpl extends AsnPsmBlockDescription {

	/**
	 * 
	 */
	public AsnPsmBlockDescriptionImpl() {
		super();
	}

	/**
	 * @param applicationId
	 * @param type
	 * @param shortName
	 * @param fullName
	 * @param documentation
	 * @param range
	 * @param optional
	 * @param isAbstract
	 */
	public AsnPsmBlockDescriptionImpl(Integer applicationId, String type,
			String shortName, String fullName, String documentation,
			String range, boolean optional, boolean isAbstract) {
		super(applicationId, type, shortName, fullName, documentation, range, optional, isAbstract);
	}


	/**
	 * @param otherBean
	 */
	public AsnPsmBlockDescriptionImpl(AsnPsmBlockDescription otherBean) {
		super(otherBean);
	}
}
