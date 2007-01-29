package de.tmobile.cabu.db4o;

import com.db4o.*;
import com.db4o.messaging.*;

/** *//**
 * stops the db4o Server started with {@link StartServer}.
 * <br><br>This is done by opening a client connection
 * to the server and by sending a StopServer object as
 * a message. {@link StartServer} will react in it's
 * processMessage method.
 */

public class MessageStopServer  {

}