package de.tmobile.cabu;

import java.sql.SQLException;

public abstract class CListableListObject extends CListableObject {

	
	abstract public void clear();
	abstract public void refresh(TTConnection connection) throws SQLException;	

}
