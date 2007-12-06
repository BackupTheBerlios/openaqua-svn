/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public abstract class BaseListElement extends BaseList {
	final private int parentId;
	final private BaseElement parent;

	public BaseListElement(final int parentId, final BaseElement parent) {
		this.parentId = parentId;
		this.parent = parent;
	}


	public void buildUnifiedPrintList(final String prefix, final CUnifiedTableOutput uto) {
		for (final BaseType base : values()) {
			((TElementTmpl) base).buildUnifiedPrintList(prefix, uto);
		}
	}

	public BaseElement getParent() {
		return parent;
	}

	public int getParentId() {
		return parentId;
	}


	@Override
	public String getPrintDescription() {
		return null;
	}


	@Override
	public String getPrintHeader(final String prefix) {
		return null;
	}


}
