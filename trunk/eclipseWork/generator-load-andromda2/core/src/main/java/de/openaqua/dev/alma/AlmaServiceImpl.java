// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package de.openaqua.dev.alma;

import java.util.Iterator;
import java.util.List;



/**
 * @see de.openaqua.dev.alma.AlmaService
 */
public class AlmaServiceImpl
    extends de.openaqua.dev.alma.AlmaServiceBase
{

    /**
     * @see de.openaqua.dev.alma.AlmaService#getBudgetByMsisdn(java.lang.String)
     */
    protected de.openaqua.dev.alma.BudgetVO[] handleGetBudgetByMsisdn(java.lang.String msisdn)
        throws java.lang.Exception
    {
        // @todo implement protected de.openaqua.dev.alma.BudgetVO[] handleGetBudgetByMsisdn(java.lang.String msisdn)
        return null;
    }

    /**
     * @see de.openaqua.dev.alma.AlmaService#createBudgetTemplate(de.openaqua.dev.alma.BudgetTemplateVO)
     */
    protected void handleCreateBudgetTemplate(de.openaqua.dev.alma.BudgetTemplateVO budgetTemplate)
        throws java.lang.Exception
    {
        // @todo implement protected void handleCreateBudgetTemplate(de.openaqua.dev.alma.BudgetTemplateVO budgetTemplate)
        throw new java.lang.UnsupportedOperationException("de.openaqua.dev.alma.AlmaService.handleCreateBudgetTemplate(de.openaqua.dev.alma.BudgetTemplateVO budgetTemplate) Not implemented!");
    }

    /**
     * @see de.openaqua.dev.alma.AlmaService#createBudgetForMsisdn(de.openaqua.dev.alma.BudgetVO)
     */
    protected void handleCreateBudgetForMsisdn(de.openaqua.dev.alma.BudgetVO budget)
        throws java.lang.Exception
    {
        // @todo implement protected void handleCreateBudgetForMsisdn(de.openaqua.dev.alma.BudgetVO budget)
        throw new java.lang.UnsupportedOperationException("de.openaqua.dev.alma.AlmaService.handleCreateBudgetForMsisdn(de.openaqua.dev.alma.BudgetVO budget) Not implemented!");
    }

	/* (non-Javadoc)
	 * @see de.openaqua.dev.alma.AlmaServiceBase#handleCreateContract(java.lang.String, java.lang.String, int, int)
	 */
	@Override
	protected void handleCreateContract(String msisdn, String contract, int validFrom, int validTo) throws Exception {
		Contract c = Contract.Factory.newInstance(validFrom, validTo, msisdn, contract);
    	getContractDao().create(c);
	}

	/* (non-Javadoc)
	 * @see de.openaqua.dev.alma.AlmaServiceBase#handleGetContractsByMsisdn(java.lang.String)
	 */
	@Override
	protected List handleGetContractsByMsisdn(String msisdn) throws Exception {
		return getContractDao().findByMsisdn(ContractDao.TRANSFORM_CONTRACTVO, msisdn);
	}

	/* (non-Javadoc)
	 * @see de.openaqua.dev.alma.AlmaServiceBase#handleGetContractsByMsisdn(java.lang.String)
	 */
	/*
	@Override
	protected ContractVO[] handleGetContractsByMsisdn(String msisdn) throws Exception {
		List<?> list = getContractDao().findByMsisdn(ContractDao.TRANSFORM_CONTRACTVO, msisdn);
		for(Object e : list) {
		    if (e == null)
		        System.out.println("null");
		    else
		        System.out.println(e.getClass());
		}
		ContractVO[] result = (ContractVO[]) list.toArray();
		System.err.println("bye");
		return result;
	}
	*/


}