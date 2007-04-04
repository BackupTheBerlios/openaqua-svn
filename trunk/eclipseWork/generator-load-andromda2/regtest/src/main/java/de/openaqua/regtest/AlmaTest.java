package de.openaqua.regtest;

import java.util.List;

import de.openaqua.dev.alma.crud.ContractManageableService;
import de.openaqua.dev.alma.crud.CounterTemplateManageableService;

public class AlmaTest extends RegTest {
	final int maxContracts = 10;
	final int maxCounterTemplates = 10;
	public AlmaTest(String name) {
		super(name);
	}


	public boolean RunTest() {
		if (createContract() != true) return false;
		if (createCounterTemplate() != true) return false;
		return true;
	}
	
	
	public boolean createContract() {
		ContractManageableService cms = (ContractManageableService) getBeanFactory().getFactory().getBean("ContractManageableService", ContractManageableService.class);
		if (cms == null) {
			logger().error("got no ContractManageableService service reference");
			return false;
		}
		
		for (int i = 0; i < maxContracts;++i) {
			String msisdn = "" + i;
			int validTo = 0;
			java.lang.Long[] budgets = new java.lang.Long[0];
			List list;
			try {
				list = cms.read(msisdn, null, 0, 0, 0L, budgets);
				if (list.isEmpty()){
					//1136139540 = 2006-01-01T19:19:00
					cms.create(msisdn, msisdn, 1136139540, validTo, 0L, budgets);
				}
			} catch (Exception e) {
				e.printStackTrace();
				return false;
			}
			
		}
		return true;
	}

	public boolean createCounterTemplate() {
		CounterTemplateManageableService cms = (CounterTemplateManageableService) getBeanFactory().getFactory().getBean("CounterTemplateManageableService");
		if (cms == null) {
			logger().error("got no CounterTemplateManageableService service reference");
			return false;
		}
		
		for (long id = 1; id <= maxCounterTemplates;++id) {
			List list;
			try {
				list = cms.read(0, id);
				if (list.isEmpty()){
					cms.create(10, id);
				}
			} catch (Exception e) {
				e.printStackTrace();
				return false;
			}
			
		}
		return true;
	}

}
