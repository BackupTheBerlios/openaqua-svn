/**
 * 
 */
package de.tmobile.cabu.db4o;


/**
 * @author behrenan
 *
 */
public class ContractKey {
	final private Integer key;

	public ContractKey(int key)         { 
		this.key = new Integer(key);
	}

	/**
	 * @return the key
	 */
	public Integer getKey() {
		return key;
	}

	/* (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		final int PRIME = 31;
		int result = 1;
		result = PRIME * result + ((key == null) ? 0 : key.hashCode());
		return result;
	}

	/* (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		final ContractKey other = (ContractKey) obj;
		if (key == null) {
			if (other.key != null)
				return false;
		} else if (!key.equals(other.key))
			return false;
		return true;
	}

}
