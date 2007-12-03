/**
 * 
 */
package de.tmobile.cabu;

/**
 * @author behrenan
 * 
 */
public class CIdentification_TypeBase extends CBaseType {
	public static String getPrintHeader(final String prefix) {
		String result = "prefix" + sep() + sep() + sep();
		result += "id" + sep();
		result += "sorting" + sep();
		result += "valid" + sep();
		result += "descriptionId" + sep();
		result += "description";
		return result;
	}

	int desription;
	int sorting;
	int valid;

	public CIdentification_TypeBase(final int id, final int descriptionId, final int sorting, final int valid) {
		super(id, 0, null, null);
		desription = descriptionId;
		this.sorting = sorting;
		this.valid = valid;
	}

	public int getDesription() {
		return desription;
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
		result += getDesription() + sep();
		final CBaseType base = CDescriptionList.getInstances().get(getDesription());
		if (base instanceof CDescription) {
			final CDescription desc = (CDescription) base;
			result += desc.getDescription();
		} else {
			result += "unknownDescription";
		}
		Logger.getRootLogger().out(result);
	}

	public void setDesription(final int desription) {
		this.desription = desription;
	}

	public void setSorting(final int sorting) {
		this.sorting = sorting;
	}

	public void setValid(final int valid) {
		this.valid = valid;
	}

}
