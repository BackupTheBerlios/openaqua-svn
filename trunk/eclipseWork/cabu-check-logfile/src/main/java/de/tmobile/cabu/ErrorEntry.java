/**
 * 
 */
package de.tmobile.cabu;

import java.util.Calendar;




/**
 * @author behrenan
 *
 */
public class ErrorEntry {
	private String atTime;
	private String vasCodeService;
	private String vasCodeGroup;
	private int usageBegin;
	private int usageEnd;
	private int refTime;
	private int tariffOwner;
	private int tariffNumber;
	private int prepay;
	private int partner;
	
	
	public ErrorEntry(LogFileLine line) {
		super();

		setAtTime(line.getTime());
		final String msg = line.getMessage();
		this.vasCodeService	= getStr(msg, "vasCodeService=");
		this.vasCodeGroup	= getStr(msg, "vasCodeGroup=");
		this.usageBegin		= getInt(msg, "usageIntervalBegin=");
		this.usageEnd		= getInt(msg, "usageIntervalEnd=");
		this.refTime 		= getInt(msg, "refTimestamp=");
		this.tariffOwner	= getInt(msg, "tariffOwner=");
		this.tariffNumber	= getInt(msg, "tariffNumber=");
		this.prepay 		= getInt(msg, "prepayIndicator=");
		this.partner		= getInt(msg, "wholesalePartnerId=");
	}
	
	protected int getInt(final String str, final String search) {
		try {
			return Integer.valueOf(getStr(str, search)).intValue();
		} catch (Exception e) {
			return 0;
		}
	}

	protected final String getStr(final String str, final String search) {
		int begin = str.indexOf(search);
		return str.substring(begin+search.length(), str.indexOf(',', begin));
	}

	protected String unixTimeToString(final long time) {
		Calendar cal = Calendar.getInstance();
		cal.setTimeInMillis(time*1000);
		return Configuration.getInstance().getDateFormat().format(cal.getTime());
	}
	
	public void print(final int spaces)  {
		//Leerstring anlegen
		String leer = new String();
		for(int i =0;i<spaces;i++) leer += " ";
		
		
		//Ausgabe des Errors
		String s = new String();
		
		s = leer;
		s += "at " + getAtTime() + ": ";
		s += " refTime    ="+unixTimeToString(refTime);
		Logger.getRootLogger().out(s);

		s = leer;
		s += "                    usageBegin ="+unixTimeToString(usageBegin);
		s += " usageEnd    ="+unixTimeToString(usageEnd);
		Logger.getRootLogger().out(s);
		
		s = leer;
		s += "                    tariffOwner="+tariffOwner;
		s += "              tariffNumber="+tariffNumber;
		Logger.getRootLogger().out(s);
		s = leer;
		s += "                    prepay     ="+prepay;
		s += "              wholesalep  ="+partner;
		Logger.getRootLogger().out(s);
		
	}
	
	public int getRefTime() {
		return this.refTime;
	}
	public void setRefTime(int refTime) {
		this.refTime = refTime;
	}
	public int getUsageBegin() {
		return this.usageBegin;
	}
	public void setUsageBegin(int usageBegin) {
		this.usageBegin = usageBegin;
	}
	public int getUsageEnd() {
		return this.usageEnd;
	}
	public void setUsageEnd(int usageEnd) {
		this.usageEnd = usageEnd;
	}
	public String getVasCodeGroup() {
		return this.vasCodeGroup;
	}
	public void setVasCodeGroup(String vasCodeGroup) {
		this.vasCodeGroup = vasCodeGroup;
	}
	public String getVasCodeService() {
		return this.vasCodeService;
	}
	public void setVasCodeService(String vasCodeService) {
		this.vasCodeService = vasCodeService;
	}

	public int getPartner() {
		return this.partner;
	}

	public void setPartner(int partner) {
		this.partner = partner;
	}

	public int getPrepay() {
		return this.prepay;
	}

	public void setPrepay(int prepay) {
		this.prepay = prepay;
	}

	public int getTariffNumber() {
		return this.tariffNumber;
	}

	public void setTariffNumber(int tariffNumber) {
		this.tariffNumber = tariffNumber;
	}

	public int getTariffOwner() {
		return this.tariffOwner;
	}

	public void setTariffOwner(int tariffOwner) {
		this.tariffOwner = tariffOwner;
	}

	/**
	 * @return the atTime
	 */
	public String getAtTime() {
		return this.atTime;
	}

	/**
	 * @param atTime the atTime to set
	 */
	public void setAtTime(String atTime) {
		this.atTime = atTime;
	}
	

}
