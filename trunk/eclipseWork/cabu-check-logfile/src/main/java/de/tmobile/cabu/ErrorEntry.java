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
	private String	atTime;
	private String	vasCodeService;
	private String	vasCodeGroup;
	private int	   usageBegin;
	private int	   usageEnd;
	private int	   refTime;
	private int	   tariffOwner;
	private int	   tariffNumber;
	private int	   prepay;
	private int	   partner;


	public ErrorEntry(final LogFileLine line) {
		super();

		setAtTime(line.getTime());
		final String msg = line.getMessage();
		vasCodeService = getStr(msg, "vasCodeService=");
		vasCodeGroup = getStr(msg, "vasCodeGroup=");
		usageBegin = getInt(msg, "usageIntervalBegin=");
		usageEnd = getInt(msg, "usageIntervalEnd=");
		refTime = getInt(msg, "refTimestamp=");
		tariffOwner = getInt(msg, "tariffOwner=");
		tariffNumber = getInt(msg, "tariffNumber=");
		prepay = getInt(msg, "prepayIndicator=");
		partner = getInt(msg, "wholesalePartnerId=");
	}


	/**
	 * @return the atTime
	 */
	public String getAtTime() {
		return atTime;
	}


	protected int getInt(final String str, final String search) {
		try {
			return Integer.valueOf(getStr(str, search)).intValue();
		} catch (final Exception e) {
			return 0;
		}
	}


	public int getPartner() {
		return partner;
	}


	public int getPrepay() {
		return prepay;
	}


	public int getRefTime() {
		return refTime;
	}


	protected final String getStr(final String str, final String search) {
		final int begin = str.indexOf(search);
		return str.substring(begin + search.length(), str.indexOf(',', begin));
	}


	public int getTariffNumber() {
		return tariffNumber;
	}


	public int getTariffOwner() {
		return tariffOwner;
	}


	public int getUsageBegin() {
		return usageBegin;
	}


	public int getUsageEnd() {
		return usageEnd;
	}


	public String getVasCodeGroup() {
		return vasCodeGroup;
	}


	public String getVasCodeService() {
		return vasCodeService;
	}


	public void print(final int spaces) {
		// Leerstring anlegen
		String leer = new String();
		for (int i = 0; i < spaces; i++) {
			leer += " ";
		}

		// Ausgabe des Errors
		String s = new String();

		s = leer;
		s += "at " + getAtTime() + ": ";
		s += " refTime=" + unixTimeToString(refTime);
		s += " tariff(Owner/Number/Prepay/SP)=";
		s += tariffOwner + "/" + tariffNumber;
		s += "/" + prepay + "/" + partner;
		Logger.getRootLogger().out(s);
		s = leer;
		s += "                    ";
		s += "usageIv=" + unixTimeToString(usageBegin) + "-" + unixTimeToString(usageEnd);
		Logger.getRootLogger().out(s);

	}


	/**
	 * @param atTime
	 *            the atTime to set
	 */
	public void setAtTime(final String atTime) {
		this.atTime = atTime;
	}


	public void setPartner(final int partner) {
		this.partner = partner;
	}


	public void setPrepay(final int prepay) {
		this.prepay = prepay;
	}


	public void setRefTime(final int refTime) {
		this.refTime = refTime;
	}


	public void setTariffNumber(final int tariffNumber) {
		this.tariffNumber = tariffNumber;
	}


	public void setTariffOwner(final int tariffOwner) {
		this.tariffOwner = tariffOwner;
	}


	public void setUsageBegin(final int usageBegin) {
		this.usageBegin = usageBegin;
	}


	public void setUsageEnd(final int usageEnd) {
		this.usageEnd = usageEnd;
	}


	public void setVasCodeGroup(final String vasCodeGroup) {
		this.vasCodeGroup = vasCodeGroup;
	}


	public void setVasCodeService(final String vasCodeService) {
		this.vasCodeService = vasCodeService;
	}


	protected String unixTimeToString(final long time) {
		final Calendar cal = Calendar.getInstance();
		cal.setTimeInMillis(time * 1000);
		return Configuration.getInstance().getDateFormat().format(cal.getTime());
	}

}
