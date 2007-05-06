// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package org.andromda.cartridges.asn.psm;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import org.andromda.metafacades.uml.ClassifierFacade;

/**
 * @see org.andromda.cartridges.asn.psm.AsnPsmAsnDescription
 */
public class AsnPsmAsnDescriptionImpl
    extends org.andromda.cartridges.asn.psm.AsnPsmAsnDescription
{
    public AsnPsmAsnDescriptionImpl()
    {
        super();
    }

    public AsnPsmAsnDescriptionImpl(java.lang.String type, java.lang.String shortName, java.lang.String fullName, java.lang.String documentation)
    {
       super(type, shortName, fullName, documentation);
    }

    public AsnPsmAsnDescriptionImpl(java.lang.String type, java.lang.String shortName, java.lang.String fullName, java.lang.String documentation, org.andromda.cartridges.asn.psm.AsnPsmFooterDescription footer, org.andromda.cartridges.asn.psm.AsnPsmHeaderDescription header, java.util.Collection details, java.util.Collection blocks)
    {
        super(type, shortName, fullName, documentation, footer, header, details, blocks);
    }

    /**
     * Copy-constructor from other AsnPsmAsnDescription
     *
     * @param otherBean, cannot be <code>null</code>
     * @throws java.lang.NullPointerException if the argument is <code>null</code>
     */
    public AsnPsmAsnDescriptionImpl(AsnPsmAsnDescription otherBean)
    {
        this(otherBean.getType(), otherBean.getShortName(), otherBean.getFullName(), otherBean.getDocumentation(), otherBean.getFooter(), otherBean.getHeader(), otherBean.getDetails(), otherBean.getBlocks());
    }


    /**
     * @see org.andromda.cartridges.asn.psm.AsnPsmAsnDescription#hasHeader()
     */
    public boolean hasHeader()
    {
    	if (getHeader() == null) {
    		return false;
    	} else {
    		return true;
    	}
    }

    
    
    /**
     * @see org.andromda.cartridges.asn.psm.AsnPsmAsnDescription#hasFoter()
     */
    public boolean hasFooter()
    {
    	if (getFooter() == null) {
    		return false;
    	} else {
    		return true;
    	}
    }

    
    
    /**
     * @see org.andromda.cartridges.asn.psm.AsnPsmAsnDescription#hasDetails()
     */
    public boolean hasDetails()
    {
    	return false;
    	
    }

    
    
    private void collectAllBlocks(ClassifierFacade clFacade, Map<String, ClassifierFacade> blocks) {
    	if (!blocks.containsKey(clFacade.getFullyQualifiedName())) {
        	error("found block"+clFacade.getFullyQualifiedName());
    		blocks.put(clFacade.getFullyQualifiedName(), clFacade);
    		Collection col = clFacade.getAllAssociatedClasses();
    		Iterator it = col.iterator();
    		while (it.hasNext()) {
    			Object o = it.next();
    			if (o instanceof ClassifierFacade) {
    				collectAllBlocks((ClassifierFacade) o, blocks);
    			}
    		}
    	}
    }
    
    
    
    private void extractHeaderFromBlocks(Map<String, ClassifierFacade> blocks) {
    	Iterator it = blocks.values().iterator();
    	while(it.hasNext()) {
    		Object o = it.next();
    		if (o instanceof ClassifierFacade) {
    			ClassifierFacade cl = (ClassifierFacade) o;
    			if (cl.hasStereotype("AsnHeader")){
    				AsnPsmHeaderDescription  header = new AsnPsmHeaderDescription();
    				header.buildFromClassifier(cl);
    				this.setHeader(header);
    				blocks.remove(cl.getFullyQualifiedName());
    				return;
    			}
    		}
    	}
    }

    
    
    private void extractFooterFromBlocks(Map<String, ClassifierFacade> blocks) {
    	Iterator it = blocks.values().iterator();
    	while(it.hasNext()) {
    		Object o = it.next();
    		if (o instanceof ClassifierFacade) {
    			ClassifierFacade cl = (ClassifierFacade) o;
    			if (cl.hasStereotype("AsnFooter")){
    				AsnPsmFooterDescription  footer = new AsnPsmFooterDescription();
    				footer.buildFromClassifier(cl);
    				this.setFooter(footer);
    				blocks.remove(cl.getFullyQualifiedName());
    				return;
    			}
    		}
    	}
    }

    
    
    private void extractDetailsFromBlocks(Map<String, ClassifierFacade> blocks) {
    	Iterator it = blocks.values().iterator();
    	Collection<AsnPsmDetailDescription> details = new ArrayList<AsnPsmDetailDescription>();
    	while(it.hasNext()) {
    		Object o = it.next();
    		if (o instanceof ClassifierFacade) {
    			ClassifierFacade cl = (ClassifierFacade) o;
    			if (cl.hasExactStereotype("ValueObject")){
    				AsnPsmDetailDescription  detail = new AsnPsmDetailDescription();
    				detail.buildFromClassifier(cl);
    				details.add(detail);
    			}
    		}
    	}
    	setBlocks(details);
    }

    
    
    @Override
    public boolean buildFromClassifier(ClassifierFacade classifier) {
    	boolean result = super.buildFromClassifier(classifier);
    	
    	//collect all possible blocks
    	Map<String, ClassifierFacade> blocks = new HashMap<String, ClassifierFacade>();
    	collectAllBlocks(classifier, blocks);
    	
    	//get header from them
    	extractHeaderFromBlocks(blocks);
    	extractFooterFromBlocks(blocks);
    	extractDetailsFromBlocks(blocks);
    	return result;
    }

	/* (non-Javadoc)
	 * @see org.andromda.cartridges.asn.psm.AsnPsmAsnDescription#isOneDetailOnly()
	 */
	@Override
	public boolean isOneDetailOnly() {
		return false;
	}


}
