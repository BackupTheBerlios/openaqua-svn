/**
 * 
 */
package de.tmobile.cabu;


import java.sql.Timestamp;


/**
 * @author behrenan
 * 
 */
public class TCounterSet extends TElement {

	public TCounterSet(final int id, final int type, final int subtype, final int datatype, final int unittype, final int parentId,
			final int rootId, final String value, final Timestamp insertTime, final int templId, final int templVers) {

		super(id, type, subtype, datatype, unittype, parentId, rootId, value, insertTime, templId, templVers);

	}
}
