/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class ListElementTmpl extends ListElementTmplPart {
	private static final long serialVersionUID = 1056598853660288338L;
	private static ListElementTmpl INSTANCE = new ListElementTmpl(0);

	public static ListElementTmpl getInstances() {
		return INSTANCE;
	}

	/**
	 * @param parentId
	 */
	public ListElementTmpl(final int parentId) {
		super(parentId, null);
	}

	@Override
	public void print(final String prefix) {
		final CUnifiedTableOutput otu = new CUnifiedTableOutput();
		ListElementTmpl.getInstances().buildUnifiedPrintList("TA_ELEMENT_TMPL", otu);
		otu.print();
	}

}
