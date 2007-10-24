/**
 * 
 */
package de.tmobile.cabu;




/**
 * @author behrenan
 *
 */
public class LogFileLine {
	private String time;
	private String system;
	private String empty;
	private String process;
	private int number;
	private String type;
	private int	id;
	private String message;
	
	
	public String getEmpty() {
		return this.empty;
	}
	public void setEmpty(String empty) {
		this.empty = empty;
	}
	public int getId() {
		return this.id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public String getMessage() {
		return this.message;
	}
	public void setMessage(String message) {
		this.message = message;
	}
	public int getNumber() {
		return this.number;
	}
	public void setNumber(int number) {
		this.number = number;
	}
	public String getProcess() {
		return this.process;
	}
	public void setProcess(String process) {
		this.process = process;
	}
	public String getSystem() {
		return this.system;
	}
	public void setSystem(String system) {
		this.system = system;
	}
	public String getTime() {
		return this.time;
	}
	public void setTime(String time) {
		this.time = time;
	}
	public String getType() {
		return this.type;
	}
	public void setType(String type) {
		this.type = type;
	}

	public void print(final int spaces)  {
	//Leerstring anlegen
	String s = new String();
	for(int i =0;i<spaces;i++) s += " ";
	
	s+=" MSG: "+message;
	Logger.getRootLogger().out(s);
	
	}
}
