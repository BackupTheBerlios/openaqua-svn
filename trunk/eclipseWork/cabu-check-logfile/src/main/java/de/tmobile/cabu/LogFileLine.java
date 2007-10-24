/**
 * 
 */
package de.tmobile.cabu;

/**
 * @author behrenan
 * 
 */
public class LogFileLine {
	private String	time;
	private String	system;
	private String	empty;
	private String	process;
	private int	   number;
	private String	type;
	private int	   id;
	private String	message;


	public String getEmpty() {
		return empty;
	}


	public int getId() {
		return id;
	}


	public String getMessage() {
		return message;
	}


	public int getNumber() {
		return number;
	}


	public String getProcess() {
		return process;
	}


	public String getSystem() {
		return system;
	}


	public String getTime() {
		return time;
	}


	public String getType() {
		return type;
	}


	public void print(final int spaces) {
		// Leerstring anlegen
		String s = new String();
		for (int i = 0; i < spaces; i++) {
			s += " ";
		}

		s += " MSG: " + message;
		Logger.getRootLogger().out(s);

	}


	public void setEmpty(final String empty) {
		this.empty = empty;
	}


	public void setId(final int id) {
		this.id = id;
	}


	public void setMessage(final String message) {
		this.message = message;
	}


	public void setNumber(final int number) {
		this.number = number;
	}


	public void setProcess(final String process) {
		this.process = process;
	}


	public void setSystem(final String system) {
		this.system = system;
	}


	public void setTime(final String time) {
		this.time = time;
	}


	public void setType(final String type) {
		this.type = type;
	}
}
