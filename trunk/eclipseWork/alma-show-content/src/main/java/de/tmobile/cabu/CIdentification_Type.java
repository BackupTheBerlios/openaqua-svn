/**
 * 
 */
package de.tmobile.cabu;

/**
 * @author behrenan
 * 
 */
public class CIdentification_Type extends CBaseType {
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

	public CIdentification_Type(final int id, final int dId, final int sorting, final int valid) {
		super(id, 0, null, null);
		desriptionId = dId;
		this.sorting = sorting;
		this.valid = valid;
	}

	public final String getDescription() {
		final CBaseType base = CDescriptionList.getInstances().get(getDesriptionId());
		if (base instanceof CDescription) {
			final CDescription desc = (CDescription) base;
			return desc.getDescription();
		} else {
			return "unknownDescription";
		}

	}

	public int getDesriptionId() {
		return desriptionId;
	}

	public int getSorting() {
		return sorting;
	}

	public int getValid() {
		return valid;
	}

	@Override
	public void print(final String prefix) {
		String result = prefix + sep();
		result += getId() + sep();
		result += getSorting() + sep();
		result += getValid() + sep();
		result += getDesriptionId() + sep();
		result += getDescription();
		Logger.getRootLogger().out(result);
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
