package de.openaqua.regtest;

import java.util.ArrayList;
import java.util.Iterator;

import java.util.List;
import java.util.Random;

import org.apache.log4j.Logger;

import de.openaqua.dev.alma.AlmaException;
import de.openaqua.dev.alma.AlmaService;
import de.openaqua.dev.alma.ContractVO;
import de.openaqua.dev.alma.crud.ContractManageableService;
import de.openaqua.dev.alma.crud.ContractValueObject;
import de.openaqua.regTestHelper.*;


public class AlmaLoadGenerator extends LoadGenerator {
	
	private final AlmaService almaService = (AlmaService)getBeanFactory().getFactory().getBean("almaService");
	private final int maxContracts = 10000;
	private final Random random = new Random();
	private final static Logger logger = Logger.getRootLogger();
	
	public AlmaLoadGenerator(boolean readTest, String threadName) {
		super(readTest, threadName);
	}


	@Override
	public LoadGenerator getNewInstance(boolean readTest, String threadName)
	{
		return new AlmaLoadGenerator(readTest, threadName);		
	}


	@Override
	public boolean cleanEnvironment()
	{
		ContractManageableService cms = (ContractManageableService) getBeanFactory().getFactory().getBean("ContractManageableService");
		
		try {
			List list = cms.readAll();
			List<Long> ids = new ArrayList<Long>();
			Iterator it = list.iterator();
			while(it.hasNext()) {
				ContractValueObject c = (ContractValueObject) it.next();
				ids.add(c.getId());
			}
			if (ids.size()> 0) {
				cms.delete(ids.toArray(new Long[0]));
			}
		} catch (Exception e) {
			printError(e);
			return false;
		}
		
		return true;
	}


	@Override
	public boolean setupEnvironment()
	{
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
					logger.error("msisdn not equals: is="+v.getMsisdn() + " should="+msisdn);
					return false;
				}
				if (! v.getContractId().equals(contractId)) {
					logger.error("contractId not equals: is="+v.getContractId()+ " should="+contractId);
					return false;
				}
				if ( v.getValidFrom() != validFrom) {
					logger.error("validFrom not equals: is="+v.getValidFrom()+ " should="+validFrom);
					return false;
				}
				if ( v.getValidTo() != validTo) {
					logger.error("validTo not equals: is="+v.getValidTo()+ " should="+validTo);
					return false;
				}
			} catch (AlmaException e) {
				printError(e);
				return false;
			}
		}
		return true;

	}


	
	
	@Override
	public boolean executeRead()  {

		//look for results
		final String msisdn = "49160"+ (1+Math.abs(random.nextInt()) % maxContracts);

		try {
			List list = almaService.getContractsByMsisdn(msisdn);
			//at least one?
			if (list.isEmpty()) {
				logger.error("No Contract found for msisdn="+msisdn);
				return false;
			}

		} catch (AlmaException e) {
			logger.error("Exception: "+e.getLocalizedMessage());
			e.printStackTrace();
			return false;
		}

		
		return true;
	}

	@Override
	public boolean executeWrite()  {
		final String msisdn = "49160"+ (1+Math.abs(random.nextInt()) % maxContracts);
		try {
			ContractVO d = (ContractVO) almaService.getContractsByMsisdn(msisdn).get(0);
			if (d != null) {
				d.setValidTo(d.getValidTo()+1);
				almaService.updateContract(d);
			}

		} catch (AlmaException e) {
			logger.error("Exception: "+e.getLocalizedMessage());
			e.printStackTrace();
			return false;
		}
		//logger().info("done lookup for misdn="+msisdn);

		return true;
	}


}
