package com.magicdraw.samples.library.inventory.service;

import java.util.Collection;
import java.util.Date;

import junit.framework.TestCase;

import org.apache.log4j.BasicConfigurator;

import com.magicdraw.samples.library.ServiceLocator;
import com.magicdraw.samples.library.inventory.entity.Book;
import com.magicdraw.samples.library.inventory.entity.Title;
import com.magicdraw.samples.library.inventory.vo.TitleSearchCriteria;

public class InventoryServiceTest extends TestCase
{
    private ServiceLocator serviceLocator;

    @Override
    protected void setUp() throws Exception
    {
        BasicConfigurator.configure();
        serviceLocator = ServiceLocator.instance();
        serviceLocator.init("testBeanRefFactory.xml");
    }

    public void testCreateBook()
    {
        InventoryService inventoryService = serviceLocator.getInventoryService();
        
        Book book = Book.Factory.newInstance("Illusions", new Date(), "Richard Bach", null, "12345678", 200);
        book = inventoryService.createBook(book);
        assertNotNull("The ID must now be non-null", book.getId());
    }
    
    public void testFindTitles() throws Exception
    {
        InventoryService inventoryService = serviceLocator.getInventoryService();

        TitleSearchCriteria criteria = new TitleSearchCriteria();
        criteria.setAuthor("%Bach%");
        Collection titles = inventoryService.findTitlesByCriteria(criteria);
        assertTrue("Titles must be found", titles.size() > 0);
        Title testTitle = (Title) titles.iterator().next();
        assertEquals("Richard Bach", testTitle.getAuthor());
        assertTrue(testTitle instanceof Book);
    }

}
