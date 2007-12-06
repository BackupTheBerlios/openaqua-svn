/**
 * 
 */
package de.tmobile.cabu;


import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;


/**
 * @author behrenan
 * 
 */
public class UnifiedTableOutput {

	Map<String, List<String>> collection;

	public UnifiedTableOutput() {
		super();
		collection = new TreeMap<String, List<String>>();
	}

	final public void add(final String type, final String line) {
		get(type).add(line);
	}


	final List<String> get(final String type) {
		if (!collection.containsKey(type)) {
			collection.put(type, new LinkedList<String>());
		}
		return collection.get(type);
	}

	final void print() {
		for (final List<String> list : collection.values()) {
			for (final String string : list) {
				Logger.getRootLogger().out(string);
			}
		}
	}
}
