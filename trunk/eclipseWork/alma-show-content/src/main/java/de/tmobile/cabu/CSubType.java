/**
 * 
 */
package de.tmobile.cabu;





/**
 * @author behrenan
 *
 */
public class CSubType extends CListableObject{
	private Integer id;
	private String description;
	
	
	public CSubType(Integer id, String description) {
		this.id = id;
		this.description = description.replaceFirst("CABU[- ]", "");
		this.description = this.description.replaceFirst("Attribut[e]?", "");
	}

	
	
	public void list(String type, Integer spaces) {
		
	}

	public String getDescription() {
		return this.description;
	}


	public Integer getId() {
		return this.id;
	}



	/* (non-Javadoc)
	 * @see de.tmobile.cabu.CListableObject#print(java.lang.String)
	 */
	@Override
	public void print(String prefix) {
		System.out.println(prefix+sep()+id+sep()+description);
	}
}
