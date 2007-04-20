// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package com.magicdraw.samples.library.inventory.service;

import java.util.Collection;

import com.magicdraw.samples.library.inventory.entity.Book;
import com.magicdraw.samples.library.inventory.vo.TitleSearchCriteria;

/**
 * @see com.magicdraw.samples.library.inventory.service.InventoryService
 */
public class InventoryServiceImpl
    extends com.magicdraw.samples.library.inventory.service.InventoryServiceBase
{

    /**
     * @see com.magicdraw.samples.library.inventory.service.InventoryService#createBook(com.magicdraw.samples.library.inventory.entity.Book)
     */
    protected Book handleCreateBook(Book book)
        throws java.lang.Exception
    {
        return (Book) getBookDao().create(book);
    }

    @Override
    protected Collection handleFindTitlesByCriteria(TitleSearchCriteria criteria) throws Exception
    {
        return getTitleDao().findTitlesByCriteria(criteria);
    }

}