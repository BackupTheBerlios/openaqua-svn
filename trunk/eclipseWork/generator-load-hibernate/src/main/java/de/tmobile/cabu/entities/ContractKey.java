/**
 * 
 */
package de.tmobile.cabu.entities;

import javax.persistence.*;

/**
 * @author behrenan
 *
 */
@Entity
@Table(name = "contractkey")
public class ContractKey {
	
	private Integer key;
	public ContractKey(Integer key)         { 
		this.key = key;
	}
	
	/**
	 * @return the key
	 */
	@Id
	public Integer getKey() {
		return key;
	}

	public void setKey(Integer key) {
		this.key = key;
	}
}
