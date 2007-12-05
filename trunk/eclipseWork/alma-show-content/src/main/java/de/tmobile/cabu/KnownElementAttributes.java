/**
 * 
 */
package de.tmobile.cabu;


import java.util.HashMap;
import java.util.Iterator;
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
public class KnownElementAttributes {
	private final static KnownElementAttributes INSTANCE = new KnownElementAttributes();

	public static KnownElementAttributes getInstances() {
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

	private KnownElementAttributes() {
		super();
	}

	public final List<Integer> getKnownElementAttributes(final int elementType) {

		final List<Integer> result = new LinkedList<Integer>(); //default empty result 
		elementReadLock.lock();

		try {
			//try to fillup result list
			if (knownElementAttributes.containsKey(elementType)) {
				final Iterator<Integer> iter = knownElementAttributes.get(elementType).iterator();
				while (iter.hasNext()) {
					result.add(iter.next());
				}
			}
		} finally {
			elementReadLock.unlock();
		}

		return result;
	}

	public final List<Integer> getKnownTemplateAttributes(final int elementType) {

		final List<Integer> result = new LinkedList<Integer>(); //default empty result 
		templateReadLock.lock();

		try {
			//try to fillup result list
			if (knownTemplateAttributes.containsKey(elementType)) {
				final Iterator<Integer> iter = knownTemplateAttributes.get(elementType).iterator();
				while (iter.hasNext()) {
					result.add(iter.next());
				}
			}
		} finally {
			templateReadLock.unlock();
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
