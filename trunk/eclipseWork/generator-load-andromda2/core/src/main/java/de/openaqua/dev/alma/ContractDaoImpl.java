// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package de.openaqua.dev.alma;
/**
 * @see de.openaqua.dev.alma.Contract
 */
public class ContractDaoImpl
    extends de.openaqua.dev.alma.ContractDaoBase
{
    /**
     * @see de.openaqua.dev.alma.ContractDao#toContractVO(de.openaqua.dev.alma.Contract, de.openaqua.dev.alma.ContractVO)
     */
    public void toContractVO(
        de.openaqua.dev.alma.Contract source,
        de.openaqua.dev.alma.ContractVO target)
    {
        // @todo verify behavior of toContractVO
        super.toContractVO(source, target);
    }


    /**
     * @see de.openaqua.dev.alma.ContractDao#toContractVO(de.openaqua.dev.alma.Contract)
     */
    public de.openaqua.dev.alma.ContractVO toContractVO(final de.openaqua.dev.alma.Contract entity)
    {
        // @todo verify behavior of toContractVO
        return super.toContractVO(entity);
    }


    /**
     * Retrieves the entity object that is associated with the specified value object
     * from the object store. If no such entity object exists in the object store,
     * a new, blank entity is created
     */
    private de.openaqua.dev.alma.Contract loadContractFromContractVO(de.openaqua.dev.alma.ContractVO contractVO)
    {
        // @todo implement loadContractFromContractVO
        throw new java.lang.UnsupportedOperationException("de.openaqua.dev.alma.loadContractFromContractVO(de.openaqua.dev.alma.ContractVO) not yet implemented.");

        /* A typical implementation looks like this:
        de.openaqua.dev.alma.Contract contract = this.load(contractVO.getId());
        if (contract == null)
        {
            contract = de.openaqua.dev.alma.Contract.Factory.newInstance();
        }
        return contract;
        */
    }

    
    /**
     * @see de.openaqua.dev.alma.ContractDao#contractVOToEntity(de.openaqua.dev.alma.ContractVO)
     */
    public de.openaqua.dev.alma.Contract contractVOToEntity(de.openaqua.dev.alma.ContractVO contractVO)
    {
        // @todo verify behavior of contractVOToEntity
        de.openaqua.dev.alma.Contract entity = this.loadContractFromContractVO(contractVO);
        this.contractVOToEntity(contractVO, entity, true);
        return entity;
    }


    /**
     * @see de.openaqua.dev.alma.ContractDao#contractVOToEntity(de.openaqua.dev.alma.ContractVO, de.openaqua.dev.alma.Contract)
     */
    public void contractVOToEntity(
        de.openaqua.dev.alma.ContractVO source,
        de.openaqua.dev.alma.Contract target,
        boolean copyIfNull)
    {
        // @todo verify behavior of contractVOToEntity
        super.contractVOToEntity(source, target, copyIfNull);
    }

}