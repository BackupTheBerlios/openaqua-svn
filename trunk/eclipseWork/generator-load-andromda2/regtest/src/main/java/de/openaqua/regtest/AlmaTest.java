package de.openaqua.regtest;

import java.util.Iterator;
import java.util.List;
import java.util.Random;

import de.openaqua.regtest.RegTest;
import de.openaqua.dev.alma.AlmaException;
import de.openaqua.dev.alma.AlmaService;
import de.openaqua.dev.alma.Contract;
import de.openaqua.dev.alma.ContractDao;
import de.openaqua.dev.alma.ContractDaoImpl;
import de.openaqua.dev.alma.ContractVO;
import de.openaqua.dev.alma.crud.ContractManageableService;
import de.openaqua.dev.alma.crud.CounterTemplateManageableService;


public class AlmaTest extends RegTest {
	final int maxContracts = 10;
	final int maxCounterTemplates = 10;
	private Random random = new Random();
	final AlmaService almaService = (AlmaService)getBeanFactory().getFactory().getBean("almaService");

	/**
	 * 
	 * @param name
	 */
	public AlmaTest(String name) {
		super(name);
	}


	public boolean RunTest() {
		//if (createCounterTemplate() != true) return false;
		if (createContractWithService() != true) return false;
		if (findContractWithService() != true) return false;
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


	public boolean createContractWithService() {
		AlmaService service = (AlmaService)getBeanFactory().getFactory().getBean("almaService");

		for (int i = 0; i < maxContracts;++i) {
			try {
				//1136139540 = 2006-01-01T19:19:00			
				service.createContract("49160"+i, ""+i, 1136139540, 0);
			} catch (AlmaException e) {
				printError(e);
				return false;
			}
		}
		return true;
	}



	/**
	 * 
	 * @return true if the test went fine
	 */
	public boolean findContractWithService() {

		//try to find n times a contract there must be at last one contract for each time
		try {
			for (int i = 0; i < maxContracts;++i) {
				//look for results
				final String msisdn = "49160"+ (Math.abs(random.nextInt()) % maxContracts);
				final ContractVO[] vos = almaService.getContractsByMsisdn(msisdn);
				
				//at least one?
				if (vos.length == 0) {
					logger().error("No Contract found for msisdn"+msisdn);
					return false;
				}
				
				//print results
				logger().info("List of MSISDNs for misdn \""+msisdn+"\"");
				for (int j = 0; j < vos.length;j++ ) {
					ContractVO d = vos[j];
					logger().info("MISDN="+d.getMsisdn()+" CONTRACT="+d.getContract());
				}
			}
			
		} catch (AlmaException e) {
			printError(e);
			return false;
		}
		
		
		return true;
	}

}
