/**
 * 
 */
package de.tmobile.cabu.db4o;

import com.db4o.ObjectContainer;
import com.db4o.messaging.MessageRecipient;

/**
 * @author behrenan
 *
 */
public class EmbeddedServerThread implements MessageRecipient{
	
	private EmbeddedServerThread () {
		super();
	}

	private EmbeddedServerThread () {
		super();
	}
	
	/* (non-Javadoc)
	 * @see com.db4o.messaging.MessageRecipient#processMessage(com.db4o.ObjectContainer, java.lang.Object)
	 */
	public void processMessage(ObjectContainer arg0, Object arg1) {
		// TODO Auto-generated method stub
		
	}

}
