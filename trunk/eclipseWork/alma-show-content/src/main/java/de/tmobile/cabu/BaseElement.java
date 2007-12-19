/**
 * 
 */
package de.tmobile.cabu;


import java.sql.Timestamp;
import java.util.Set;


/**
 * @author behrenan
 * 
 */
public abstract class BaseElement extends BaseType {

	public static String getPrintHeader(final BaseList list, final String prefix) {
		String result = BaseType.getPrintHeader(list, prefix) + sep();
		result += "Type" + sep();
		result += "SubType" + sep();
		result += "DataType" + sep();
		result += "UnitType" + sep();
		result += "rootId" + sep();
		result += "parentId";
		return result;
	}


	private final int type;
	private final int subtype;
	private final int datatype;
	private final int unittype;
	private final int parentId;
	private final int rootId;

	private final String value;

	public BaseElement(final int id, final int obj_version, final Timestamp valid_from, final Timestamp valid_to, final int type,
			final int subtype, final int datatype, final int unittype, final int parentId, final int rootId, final String value) {

		super(id, obj_version, valid_from, valid_to);

		this.type = type;
		this.subtype = subtype;
		this.datatype = datatype;
		this.unittype = unittype;
		this.parentId = parentId;
		this.rootId = rootId;
		this.value = makeValue(value);


	}


	public int getDatatype() {
		return datatype;
	}

	public int getParentId() {
		return parentId;
	}


	@Override
	public String getPrintString(final Set<Integer> attributList, final String prefix) {
		String result = super.getPrintString(attributList, prefix) + sep();
		result += ListElementType.getInstances().getTypeAsString(type) + sep();
		result += ListSubType.getInstances().getTypeAsString(subtype) + sep();
		result += ListDataType.getInstances().getTypeAsString(datatype) + sep();
		result += ListUnitType.getInstances().getTypeAsString(unittype) + sep();
		result += rootId;
		result += sep();
		result += parentId;
		result += sep();
		return result;
	}


	public int getUnittype() {
		return unittype;
	}


	public String getValue() {
		return value;
	}


}
