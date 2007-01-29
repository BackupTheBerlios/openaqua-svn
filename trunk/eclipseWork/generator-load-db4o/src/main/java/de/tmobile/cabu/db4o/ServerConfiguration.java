package de.tmobile.cabu.db4o;

import java.util.LinkedList;
import java.util.List;



public class ServerConfiguration {
	public class UserPasswordPair{
		public String user;
		public String password;
	}

	final private String   		filename;
	final private int			port;
	final private String 		hostname;
	final private List<UserPasswordPair> users;

	
	/*
	 * Creates a new EmbeddedServerConfiguration object.
	 * 
	 * @param filename - name (inclusive path) for a database file.
	 */
	public ServerConfiguration(final String filename, int port, final String hostname) {
		super();
		users = new LinkedList<UserPasswordPair>();
		this.filename = filename;
		this.port = port;
		this.hostname = hostname;
	}

	/*
	 * Creates a new EmbeddedServerConfiguration object.
	 * 
	 * @param filename - name (inclusive path) for a database file.
	 */
	public ServerConfiguration(final String filename) {
		super();
		users = new LinkedList<UserPasswordPair>();
		this.filename = filename;
		this.port = 0;
		this.hostname = "localhost";
	}
	
	
	/**
	 * @return the filename
	 */
	public final String getFilename() {
		return filename;
	}

	/**
	 * @return the hostname
	 */
	public final String getHostname() {
		return hostname;
	}

	/**
	 * @return the port
	 */
	public final int getPort() {
		return port;
	}

	/**
	 */
	public void addUser(String username, String password) {
		UserPasswordPair p = new UserPasswordPair();
		p.user = username; 
		p.password = password;
		users.add(p);		
	}

	/**
	 * @return the users
	 */
	public final List<UserPasswordPair> getUsers() {
		return users;
	}

}