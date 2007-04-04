// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package de.openaqua.dev.alma;
/**
 * @see de.openaqua.dev.alma.BudgetTemplate
 */
public class BudgetTemplateDaoImpl
    extends de.openaqua.dev.alma.BudgetTemplateDaoBase
{
    /**
     * @see de.openaqua.dev.alma.BudgetTemplateDao#toBudgetTemplateVO(de.openaqua.dev.alma.BudgetTemplate, de.openaqua.dev.alma.BudgetTemplateVO)
     */
    public void toBudgetTemplateVO(
        de.openaqua.dev.alma.BudgetTemplate source,
        de.openaqua.dev.alma.BudgetTemplateVO target)
    {
        // @todo verify behavior of toBudgetTemplateVO
        super.toBudgetTemplateVO(source, target);
    }


    /**
     * @see de.openaqua.dev.alma.BudgetTemplateDao#toBudgetTemplateVO(de.openaqua.dev.alma.BudgetTemplate)
     */
    public de.openaqua.dev.alma.BudgetTemplateVO toBudgetTemplateVO(final de.openaqua.dev.alma.BudgetTemplate entity)
    {
        // @todo verify behavior of toBudgetTemplateVO
        return super.toBudgetTemplateVO(entity);
    }


    /**
     * Retrieves the entity object that is associated with the specified value object
     * from the object store. If no such entity object exists in the object store,
     * a new, blank entity is created
     */
    private de.openaqua.dev.alma.BudgetTemplate loadBudgetTemplateFromBudgetTemplateVO(de.openaqua.dev.alma.BudgetTemplateVO budgetTemplateVO)
    {
        // @todo implement loadBudgetTemplateFromBudgetTemplateVO
        throw new java.lang.UnsupportedOperationException("de.openaqua.dev.alma.loadBudgetTemplateFromBudgetTemplateVO(de.openaqua.dev.alma.BudgetTemplateVO) not yet implemented.");

        /* A typical implementation looks like this:
        de.openaqua.dev.alma.BudgetTemplate budgetTemplate = this.load(budgetTemplateVO.getId());
        if (budgetTemplate == null)
        {
            budgetTemplate = de.openaqua.dev.alma.BudgetTemplate.Factory.newInstance();
        }
        return budgetTemplate;
        */
    }

    
    /**
     * @see de.openaqua.dev.alma.BudgetTemplateDao#budgetTemplateVOToEntity(de.openaqua.dev.alma.BudgetTemplateVO)
     */
    public de.openaqua.dev.alma.BudgetTemplate budgetTemplateVOToEntity(de.openaqua.dev.alma.BudgetTemplateVO budgetTemplateVO)
    {
        // @todo verify behavior of budgetTemplateVOToEntity
        de.openaqua.dev.alma.BudgetTemplate entity = this.loadBudgetTemplateFromBudgetTemplateVO(budgetTemplateVO);
        this.budgetTemplateVOToEntity(budgetTemplateVO, entity, true);
        return entity;
    }


    /**
     * @see de.openaqua.dev.alma.BudgetTemplateDao#budgetTemplateVOToEntity(de.openaqua.dev.alma.BudgetTemplateVO, de.openaqua.dev.alma.BudgetTemplate)
     */
    public void budgetTemplateVOToEntity(
        de.openaqua.dev.alma.BudgetTemplateVO source,
        de.openaqua.dev.alma.BudgetTemplate target,
        boolean copyIfNull)
    {
        // @todo verify behavior of budgetTemplateVOToEntity
        super.budgetTemplateVOToEntity(source, target, copyIfNull);
    }

}