/**
 * 
 */
package de.tmobile.cabu;


import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
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

	private final HashMap<Integer, TreeSet<Integer>> knownTemplateAttributes = new HashMap<Integer, TreeSet<Integer>>();
	private final HashMap<Integer, TreeSet<Integer>> knownElementAttributes = new HashMap<Integer, TreeSet<Integer>>();

	private CKnownElementAttributes() {
		super();
	}


	public void dump() {

		//dump Template Elements / Attributes
		for (final Integer i : getKnownTemplateElementTypes()) {
			String result = "Template Type " + ListElementType.getInstances().getTypeAsString(i) + " has: ";
			final List<Integer> list = getKnownTemplateAttributes(i);
			for (final Integer j : list) {
				result += j + "=" + ListElementSubtype.getInstances().getTypeAsString(j) + " ";
			}
			CLogger.getRootLogger().out(result);
		}

		//dump Element Elements / Attributes
		for (final Integer i : getKnownElementElementTypes()) {
			String result = "Template Type " + ListElementType.getInstances().getTypeAsString(i) + " has: ";
			final List<Integer> list = getKnownElementAttributes(i);
			for (final Integer j : list) {
				result += j + "=" + ListElementSubtype.getInstances().getTypeAsString(j) + " ";
			}
			CLogger.getRootLogger().out(result);
		}
	}

	public final List<Integer> getKnownElementAttributes(final int elementType) {

		final List<Integer> result = new LinkedList<Integer>(); //default empty result 
		elementReadLock.lock();

		try {
			//try to fillup result list
			if (knownElementAttributes.containsKey(elementType)) {
				for (final Integer integer : knownElementAttributes.get(elementType)) {
					result.add(integer);
				}
			}
		} finally {
			elementReadLock.unlock();
		}

		return result;
	}

	public final List<Integer> getKnownElementElementTypes() {
		final List<Integer> result = new LinkedList<Integer>();

		elementReadLock.lock();
		try {
			for (final Integer integer : knownElementAttributes.keySet()) {
				result.add(integer);
			}
		} finally {
			elementReadLock.unlock();
		}
		return result;

	}

	public final List<Integer> getKnownTemplateAttributes(final int elementType) {

		final List<Integer> result = new LinkedList<Integer>(); //default empty result 
		final Lock lock = templateReadLock;

		lock.lock();
		try {
			if (knownTemplateAttributes.containsKey(elementType)) {
				for (final Integer integer : knownTemplateAttributes.get(elementType)) {
					result.add(integer);
				}
			}
		} finally {
			lock.unlock();
		}

		return result;
	}

	public final List<Integer> getKnownTemplateElementTypes() {
		final List<Integer> result = new LinkedList<Integer>();
		final Lock lock = templateReadLock;
		lock.lock();
		try {
			for (final Integer integer : knownTemplateAttributes.keySet()) {
				result.add(integer);
			}
		} finally {
			lock.unlock();
		}
		return result;

	}

	public void setKnownElementAttributes(final int elementType, final int attributeType) {
		elementWriteLock.lock();
		try {
			//if unkwon elementType create a TreeSet
			if (!knownElementAttributes.containsKey(elementType)) {
				knownElementAttributes.put(elementType, new TreeSet<Integer>());
			}
			//store the values
			knownElementAttributes.get(elementType).add(attributeType);
		} finally {
			elementWriteLock.unlock();
		}
	}

	public void setKnownTemplateAttributes(final int elementType, final int attributeType) {
		templateWriteLock.lock();
		try {
			//if unkwon elementType create a TreeSet
			if (!knownTemplateAttributes.containsKey(elementType)) {
				knownTemplateAttributes.put(elementType, new TreeSet<Integer>());
			}
			//store the values
			knownTemplateAttributes.get(elementType).add(attributeType);
		} finally {
			templateWriteLock.unlock();
		}
	}

}
