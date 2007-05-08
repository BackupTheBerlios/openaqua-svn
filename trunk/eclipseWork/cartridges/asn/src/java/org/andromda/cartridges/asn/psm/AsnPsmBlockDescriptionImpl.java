/**
 * 
 */
package org.andromda.cartridges.asn.psm;

import java.util.ArrayList;
import java.util.Collection;

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
		Collection<AsnPsmElementDescription> elements = new ArrayList<AsnPsmElementDescription>();
		this.setElements(elements);	
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
		Collection<AsnPsmElementDescription> elements = new ArrayList<AsnPsmElementDescription>();
		this.setElements(elements);	
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
	 * @param elements
	 */
	public AsnPsmBlockDescriptionImpl(Integer applicationId, String type,
			String shortName, String fullName, String documentation,
			String range, boolean optional, boolean isAbstract,
			Collection elements) {
		super(applicationId, type, shortName, fullName, documentation, range,
				optional, isAbstract, elements);
	}

	/**
	 * @param otherBean
	 */
	public AsnPsmBlockDescriptionImpl(AsnPsmBlockDescription otherBean) {
		super(otherBean);
	}
}
