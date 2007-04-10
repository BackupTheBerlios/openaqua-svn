// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package de.openaqua.dev.alma;

import java.util.List;



/**
 * @see de.openaqua.dev.alma.AlmaService
 */
public class AlmaServiceImpl
    extends de.openaqua.dev.alma.AlmaServiceBase
{

	/* (non-Javadoc)
	 * @see de.openaqua.dev.alma.AlmaServiceBase#handleGetContractsByMsisdn(java.lang.String)
	 */
	/*
	@Override
	protected List handleGetContractsByMsisdn(String msisdn) throws Exception {
		return getContractDao().findByMsisdn(ContractDao.TRANSFORM_CONTRACTVO, msisdn);
	}
	*/

	@Override
	protected ContractVO handleCreateContract(ContractVO contractVO) throws Exception {
		Contract c = Contract.Factory.newInstance();
		c.setContractId(contractVO.getContractId());
		c.setMsisdn(contractVO.getMsisdn());
		c.setValidFrom(contractVO.getValidFrom());
		c.setValidTo(contractVO.getValidTo());
		return (ContractVO) getContractDao().create(ContractDao.TRANSFORM_CONTRACTVO, getContractDao().create(c));
	}

	@Override
	protected ContractVO handleTerminateContract(ContractVO contract) throws Exception {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	protected ContractVO handleUpdateContract(ContractVO contract) throws Exception {
		getContractDao().update(getContractDao().contractVOToEntity(contract));		
		return contract;
	}

	@Override
	protected List handleGetAllContracts() throws Exception {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	protected List handleGetContractsByExample(ContractVO contract) throws Exception {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	protected List handleGetContractsByMsisdn(String msisdn) throws Exception {
		return getContractDao().findByMsisdn(ContractDao.TRANSFORM_CONTRACTVO, msisdn);
	}


}