/**
 * 
 */
package de.tmobile.cabu;


/**
 * @author behrenan
 * 
 */
public class TDataType extends BaseType {
	public static String getPrintHeader(final String prefix) {
		String result = "prefix" + sep() + sep() + sep();
		result += "id" + sep();
		result += "sorting" + sep();
		result += "valid" + sep();
		result += "descId" + sep();
		result += "description";
		return result;
	}

	int desriptionId;
	int sorting;
	int valid;

	public TDataType(final int id, final int dId, final int sorting, final int valid) {
		super(id, 0, null, null);
		desriptionId = dId;
		this.sorting = sorting;
		this.valid = valid;
	}

	public final String getDescription() {
		final BaseType base = ListDescription.getInstances().get(getDesriptionId());
		if (base instanceof TDescription) {
			return ((TDescription) base).getDescription();
		} else {
			return "unknownDescription";
		}

	}

	public int getDesriptionId() {
		return desriptionId;
	}

	@Override
	public String getPrintString(final String prefix) {
		String result = prefix + sep();
		result += getId();
		result += sep();
		result += getSorting();
		result += sep();
		result += getValid();
		result += sep();
		result += getDesriptionId();
		result += sep();
		result += getDescription();
		return result;
	}

	public int getSorting() {
		return sorting;
	}

	public int getValid() {
		return valid;
	}

	public void setDesriptionId(final int desription) {
		desriptionId = desription;
	}

	public void setSorting(final int sorting) {
		this.sorting = sorting;
	}

	public void setValid(final int valid) {
		this.valid = valid;
	}

}
