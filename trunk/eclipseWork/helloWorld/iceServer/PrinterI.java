package iceServer;

import Demo._PrinterDisp;
import Ice.Current;

public class PrinterI extends _PrinterDisp {

	public PrinterI() {
		super();
	}

	public void printString(String s, Current current) {
		System.out.println("Server: " + s);
		
	}

}
