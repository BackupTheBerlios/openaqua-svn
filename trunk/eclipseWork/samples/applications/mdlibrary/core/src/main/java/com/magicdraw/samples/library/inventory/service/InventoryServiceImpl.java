// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package com.magicdraw.samples.library.inventory.service;

import java.util.Collection;

import com.magicdraw.samples.library.inventory.domain.Title;

/**
 * @see com.magicdraw.samples.library.inventory.service.InventoryService
 */
public class InventoryServiceImpl
    extends com.magicdraw.samples.library.inventory.service.InventoryServiceBase
{

    /** 
     * {@inheritDoc}
     */
    protected void handleSaveBook(com.magicdraw.samples.library.inventory.domain.Book b)
        throws java.lang.Exception
    {
        getBookDao().create(b);
    }

    /** 
     * {@inheritDoc}
     */
    protected Title[] handleFindTitlesByCriteria(com.magicdraw.samples.library.inventory.vo.TitleSearchCriteria criteria)
        throws java.lang.Exception
    {
        try
        {
            Collection titlesFound = getTitleDao().findTitlesByCriteria(criteria);
            return (Title[]) titlesFound.toArray(new Title[]{});
        }
        catch (Exception e)
        {
            e.printStackTrace();
            throw e;
        }
    }

    /** 
     * {@inheritDoc}
     */
    protected Title handleLoadTitle(Long titleId) throws Exception
    {
        return getTitleDao().load(titleId);
    }

}