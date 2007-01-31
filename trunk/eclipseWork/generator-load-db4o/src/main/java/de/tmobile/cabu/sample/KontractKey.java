package de.tmobile.cabu.sample;
import java.io.File;
import java.util.List;
import java.util.Random;

import com.db4o.Db4o;
import com.db4o.ObjectContainer;
import com.db4o.config.annotations.Indexed;
import com.db4o.query.Predicate;

public class KontractKey {
	class KontractKeyKey {
		@Indexed
		public int keykey;
	}

	@Indexed
	private KontractKeyKey key;
	private int value;

	public KontractKey(int key) {
		this.key = new KontractKeyKey();
		this.key.keykey = key;
		this.value = key;
	}

	public int getKey() {
		return key.keykey;
	}




	public static void main(String[] args) {
		int STORED_OBJECTS = 50000;
		int RETRIEVED_OBJECTS = 100;

		// Delete the old database
		new File("test.yap").delete();

		ObjectContainer oc = Db4o.openFile("test.yap");

		// Store objects in batches
		for (int i = 0; i < STORED_OBJECTS; i++) {
			oc.set(new KontractKey(i));
			if (i % 10000 == 0) {
				System.out.println("Store: " + i);
				oc.commit();
			}
		}
		oc.commit();
		oc.close();

		// Retrieve objects
		oc = Db4o.openFile("test.yap");
		long start = System.currentTimeMillis();
		for (int i = 0; i < RETRIEVED_OBJECTS; i++) {
			final int contractID = Math.abs(new Random().nextInt(STORED_OBJECTS));
			List<KontractKey> ccl = oc.query(new Predicate<KontractKey>() {
				public boolean match(KontractKey c) {
					return c.getKey() == contractID;
				}
			});
			KontractKey key = ccl.listIterator().next();
			if (key.getKey() == i) {
				System.out.println("Benchmarking is fun...");
			}
		}
		long finish = System.currentTimeMillis();

		System.out.println(RETRIEVED_OBJECTS + " objects in " +  (finish - start) / 1000.0 + " seconds.");

		oc.close();
	}

}