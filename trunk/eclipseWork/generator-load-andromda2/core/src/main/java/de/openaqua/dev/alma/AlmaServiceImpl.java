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

    /**
     * @see de.openaqua.dev.alma.AlmaService#createContract(java.lang.String, java.lang.String, int, int)
     */
    protected void handleCreateContract(java.lang.String msisdn, java.lang.String contract, int validFrom, int validTo)
        throws java.lang.Exception
    {
    	Contract c = Contract.Factory.newInstance(msisdn, contract, validFrom, validTo);
    	getContractDao().create(c);
    }

	@SuppressWarnings("unchecked")
	@Override
	protected ContractVO[] handleGetContractsByMsisdn(String msisdn) throws Exception {
		return  (ContractVO[]) getContractDao().findByMsisdn(ContractDao.TRANSFORM_CONTRACTVO, msisdn).toArray(new ContractVO[0]);
	}

}