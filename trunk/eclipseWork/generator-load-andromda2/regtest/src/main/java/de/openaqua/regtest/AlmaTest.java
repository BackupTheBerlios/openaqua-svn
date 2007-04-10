package de.openaqua.regtest;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

import de.openaqua.dev.alma.AlmaException;
import de.openaqua.dev.alma.AlmaService;
import de.openaqua.dev.alma.ContractVO;
import de.openaqua.dev.alma.crud.ContractManageableService;
import de.openaqua.dev.alma.crud.ContractValueObject;
import de.openaqua.dev.alma.crud.CounterTemplateManageableService;
import de.openaqua.regtest.RegTest;


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
		//if (cleanAllContracts() != true) return false;
		//if (createCounterTemplate() != true) return false;
		//if (createContractWithService() != true) return false;
		//if (findContractWithService() != true) return false;
		//if (updateContractWithService() != true) return false;
		if (RunLoadTest() != true) return false;

		return true;
	}


	public boolean RunLoadTest() {
		logger().info("### RunLoadTest()");
		return new AlmaLoadGenerator(true, "").fireUpLoadTest();
		
	}
	
	public boolean cleanAllContracts() {
		logger().info("### cleanAllContracts()");
		ContractManageableService cms = (ContractManageableService) getBeanFactory().getFactory().getBean("ContractManageableService");
		
		try {
			List list = cms.readAll();
			List<Long> ids = new LinkedList<Long>();
			Iterator it = list.iterator();
			while(it.hasNext()) {
				ContractValueObject c = (ContractValueObject) it.next();
				ids.add(c.getId());
			}
			if (ids.size() > 0 ) {
				cms.delete(ids.toArray(new Long[0]));
			}
		} catch (Exception e) {
			printError(e);
			return false;
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
		logger().info("### createContractWithService()");


		for (int i = 1; i <= maxContracts;++i) {
			String msisdn = "49160"+i;
			String contractId = "ctrct"+i;
			int validFrom = 1136139540; //1136139540 = 2006-01-01T19:19:00
			int validTo = 0;
			try {
							
				ContractVO v = new ContractVO();
				v.setMsisdn(msisdn);
				v.setValidFrom(validFrom);
				v.setValidTo(validTo);
				v.setContractId(contractId);
				v = almaService.createContract(v);
				
				if (! v.getMsisdn().equals(msisdn)) {
					logger().error("msisdn not equals: is="+v.getMsisdn() + " should="+msisdn);
					return false;
				}
				if (! v.getContractId().equals(contractId)) {
					logger().error("contractId not equals: is="+v.getContractId()+ " should="+contractId);
					return false;
				}
				if ( v.getValidFrom() != validFrom) {
					logger().error("validFrom not equals: is="+v.getValidFrom()+ " should="+validFrom);
					return false;
				}
				if ( v.getValidTo() != validTo) {
					logger().error("validTo not equals: is="+v.getValidTo()+ " should="+validTo);
					return false;
				}
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
		logger().info("### findContractWithService()");

		//try to find n times a contract there must be at last one contract for each time
		for (int i = 0; i < maxContracts;++i) {
			//look for results
			final String msisdn = "49160"+ (1+Math.abs(random.nextInt()) % maxContracts);
			//logger().info("Try lookup for misdn="+msisdn);
			try {
				List list = almaService.getContractsByMsisdn(msisdn);

				//at least one?
				if (list.isEmpty()) {
					logger().error("No Contract found for msisdn="+msisdn);
					return false;
				}

				/*
				//print results
				logger().info("List of MSISDNs for misdn \""+msisdn+"\"");
				Iterator it = list.iterator();
				while(it.hasNext()) {
					ContractVO d = (ContractVO) it.next();
					logger().info("MISDN="+d.getMsisdn()+" CONTRACT="+d.getContractId()+" VAL_FROM="+d.getValidFrom()+ " VAL_TO="+d.getValidTo());
				}
				*/

			} catch (AlmaException e) {
				printError(e);
				return false;
			}
			//logger().info("done lookup for misdn="+msisdn);

		}



		return true;
	}

	/**
	 * 
	 * @return true if the test went fine
	 */
	public boolean updateContractWithService() {
		logger().info("### updateContractWithService()");

		//try to find n times a contract there must be at last one contract for each time
		for (int i = 0; i < maxContracts;++i) {
			//look for results
			final String msisdn = "49160"+ (1+Math.abs(random.nextInt()) % maxContracts);
			try {
				List list = almaService.getContractsByMsisdn(msisdn);
				Iterator it = list.iterator();
				while(it.hasNext()) {
					ContractVO d = (ContractVO) it.next();
					d.setValidTo(d.getValidTo()+1);
					almaService.updateContract(d);
					//logger().info("MISDN="+d.getMsisdn()+" CONTRACT="+d.getContractId()+" VAL_FROM="+d.getValidFrom()+ " VAL_TO="+d.getValidTo());
				}

			} catch (AlmaException e) {
				printError(e);
				return false;
			}
			//logger().info("done lookup for misdn="+msisdn);

		}



		return true;
	}
}
