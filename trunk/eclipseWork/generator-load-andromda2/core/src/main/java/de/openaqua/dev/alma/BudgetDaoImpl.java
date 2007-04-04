// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package de.openaqua.dev.alma;
/**
 * @see de.openaqua.dev.alma.Budget
 */
public class BudgetDaoImpl
    extends de.openaqua.dev.alma.BudgetDaoBase
{
    /**
     * @see de.openaqua.dev.alma.BudgetDao#toBudgetVO(de.openaqua.dev.alma.Budget, de.openaqua.dev.alma.BudgetVO)
     */
    public void toBudgetVO(
        de.openaqua.dev.alma.Budget source,
        de.openaqua.dev.alma.BudgetVO target)
    {
        // @todo verify behavior of toBudgetVO
        super.toBudgetVO(source, target);
    }


    /**
     * @see de.openaqua.dev.alma.BudgetDao#toBudgetVO(de.openaqua.dev.alma.Budget)
     */
    public de.openaqua.dev.alma.BudgetVO toBudgetVO(final de.openaqua.dev.alma.Budget entity)
    {
        // @todo verify behavior of toBudgetVO
        return super.toBudgetVO(entity);
    }


    /**
     * Retrieves the entity object that is associated with the specified value object
     * from the object store. If no such entity object exists in the object store,
     * a new, blank entity is created
     */
    private de.openaqua.dev.alma.Budget loadBudgetFromBudgetVO(de.openaqua.dev.alma.BudgetVO budgetVO)
    {
        // @todo implement loadBudgetFromBudgetVO
        throw new java.lang.UnsupportedOperationException("de.openaqua.dev.alma.loadBudgetFromBudgetVO(de.openaqua.dev.alma.BudgetVO) not yet implemented.");

        /* A typical implementation looks like this:
        de.openaqua.dev.alma.Budget budget = this.load(budgetVO.getId());
        if (budget == null)
        {
            budget = de.openaqua.dev.alma.Budget.Factory.newInstance();
        }
        return budget;
        */
    }

    
    /**
     * @see de.openaqua.dev.alma.BudgetDao#budgetVOToEntity(de.openaqua.dev.alma.BudgetVO)
     */
    public de.openaqua.dev.alma.Budget budgetVOToEntity(de.openaqua.dev.alma.BudgetVO budgetVO)
    {
        // @todo verify behavior of budgetVOToEntity
        de.openaqua.dev.alma.Budget entity = this.loadBudgetFromBudgetVO(budgetVO);
        this.budgetVOToEntity(budgetVO, entity, true);
        return entity;
    }


    /**
     * @see de.openaqua.dev.alma.BudgetDao#budgetVOToEntity(de.openaqua.dev.alma.BudgetVO, de.openaqua.dev.alma.Budget)
     */
    public void budgetVOToEntity(
        de.openaqua.dev.alma.BudgetVO source,
        de.openaqua.dev.alma.Budget target,
        boolean copyIfNull)
    {
        // @todo verify behavior of budgetVOToEntity
        super.budgetVOToEntity(source, target, copyIfNull);
    }

}