/**
 * 
 */
package de.tmobile.xoxi;

/**
 * @author behrenan
 *
 */
public class Error6Entry {
	private String vasCodeService;
	private String vasCodeGroup;
	private int usageBegin;
	private int usageEnd;
	private int refTime;
	private int tariffOwner;
	private int tariffNumber;
	private int prepay;
	private int partner;
	
	public Error6Entry(LogFileLine line) {
		super();
		final String msg = line.getMessage();
		this.tariffNumber	= getInt(msg, "tariffNumber=");
		this.tariffOwner	= getInt(msg, "tariffOwner=");
		this.prepay 		= getInt(msg, "prepayIndicator=");
		this.partner		= getInt(msg, "wholesalePartnerId=");
		this.refTime 		= getInt(msg, "refTimestamp=");
		this.usageBegin		= getInt(msg, "usageIntervalBegin=");
		this.usageEnd		= getInt(msg, "usageIntervalEnd=");
		this.vasCodeGroup	= getStr(msg, "vasCodeGroup=");
		this.vasCodeService	= getStr(msg, "vasCodeService=");
	}
	
	protected int getInt(final String str, final String search) {
		try {
			return Integer.valueOf(getStr(str, search)).intValue();
		} catch (Exception e) {
			return 0;
		}
	}

	protected final String getStr(final String str, final String search) {
		try {
			int begin = str.indexOf(search);
			int length = str.indexOf(',', begin);
			return str.substring(begin, length);
		} catch (Exception e) {
			return "";
		}
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
	

}
