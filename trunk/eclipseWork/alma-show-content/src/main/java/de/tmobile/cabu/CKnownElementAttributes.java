/**
 * 
 */
package de.tmobile.cabu;


import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;


/**
 * @author behrenan
 * 
 */
public class CKnownElementAttributes {
	private final static CKnownElementAttributes INSTANCE = new CKnownElementAttributes();

	public static CKnownElementAttributes getInstances() {
		return INSTANCE;
	}


	private final ReadWriteLock templateLock = new ReentrantReadWriteLock();
	private final Lock templateReadLock = templateLock.readLock();
	private final Lock templateWriteLock = templateLock.writeLock();

	private final ReadWriteLock ElementLock = new ReentrantReadWriteLock();
	private final Lock elementReadLock = ElementLock.readLock();
	private final Lock elementWriteLock = ElementLock.writeLock();

	private final Map<Integer, Set<Integer>> knownTemplateAttributes = new TreeMap<Integer, Set<Integer>>();
	private final Map<Integer, Set<Integer>> knownElementAttributes = new TreeMap<Integer, Set<Integer>>();

	private CKnownElementAttributes() {
		super();
	}


	public void dump() {
		dump("TmplType", knownTemplateAttributes);
		dump("ElemType", knownElementAttributes);
	}

	private void dump(final String type, final Map<Integer, Set<Integer>> map) {
		for (final Integer i : map.keySet()) {
			String result = type + ' ' + ListElementType.getInstances().getTypeAsString(i) + " has: ";
			for (final Integer j : map.get(i)) {
				result += j + "=" + ListElementSubtype.getInstances().getTypeAsString(j) + " ";
			}
			CLogger.getRootLogger().out(result);
		}

	}

	private final List<Integer> getKnownAttributes(final Lock lock, final Map<Integer, Set<Integer>> map, final int elementType) {
		final List<Integer> result = new LinkedList<Integer>(); //default empty result
		lock.lock();
		try {
			if (map.containsKey(elementType)) {
				for (final Integer integer : map.get(elementType)) {
					result.add(integer);
				}
			}
		} finally {
			lock.unlock();
		}
		return result;
	}

	public final List<Integer> getKnownElementAttributes(final int elementType) {
		return getKnownAttributes(elementReadLock, knownElementAttributes, elementType);
	}


	public final List<Integer> getKnownElementElementTypes() {
		return getKnownTypes(elementReadLock, knownElementAttributes);
	}


	public final List<Integer> getKnownTemplateAttributes(final int elementType) {
		return getKnownAttributes(templateReadLock, knownTemplateAttributes, elementType);
	}


	public final List<Integer> getKnownTemplateElementTypes() {
		return getKnownTypes(templateReadLock, knownTemplateAttributes);
	}


	private final List<Integer> getKnownTypes(final Lock lock, final Map<Integer, Set<Integer>> map) {
		final List<Integer> result = new LinkedList<Integer>();
		lock.lock();
		try {
			for (final Integer integer : map.keySet()) {
				result.add(integer);
			}
		} finally {
			lock.unlock();
		}
		return result;

	}

	private void setKnownAttributes(final Lock readLock, final Lock writeLock, final Map<Integer, Set<Integer>> map, final int elementType,
			final int attributeType) {

		//Test whether already exists
		readLock.lock();
		try {
			final Set<Integer> set = map.get(elementType);
			if (set != null) {
				if (set.contains(attributeType)) { return; }
			}
		} finally {
			readLock.unlock();
		}


		//otherwise write value
		writeLock.lock();
		try {
			if (!map.containsKey(elementType)) {
				map.put(elementType, new TreeSet<Integer>());
			}
			map.get(elementType).add(attributeType);
		} finally {
			writeLock.unlock();
		}
	}

	public void setKnownElementAttributes(final int elementType, final int attributeType) {
		//CLogger.getRootLogger().debug("ElemenType=" + elementType + " attrType=" + attributeType);
		setKnownAttributes(elementReadLock, elementWriteLock, knownElementAttributes, elementType, attributeType);
	}

	public void setKnownTemplateAttributes(final int elementType, final int attributeType) {
		setKnownAttributes(templateReadLock, templateWriteLock, knownTemplateAttributes, elementType, attributeType);
	}

}
