package com.magicdraw.samples.library.inventory;

import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;

import org.apache.log4j.BasicConfigurator;

import junit.framework.TestCase;

import com.magicdraw.samples.library.ServiceLocator;
import com.magicdraw.samples.library.inventory.domain.Book;
import com.magicdraw.samples.library.inventory.service.InventoryService;

public class InventoryServiceTest extends TestCase
{
    private ServiceLocator serviceLocator;

    @Override
    protected void setUp() throws Exception
    {
        super.setUp();
        BasicConfigurator.configure();
        this.serviceLocator = ServiceLocator.instance();
        this.serviceLocator.init("testBeanRefFactory.xml");
    }

    public void testSaveBook() throws Exception
    {
        InventoryService inventoryService = ServiceLocator.instance().getInventoryService();
        Book book = Book.Factory.newInstance("Illusions", today(), "Richard Bach", "Dell Publishing Company", null,
                "978-0440204886", 192);
        inventoryService.saveBook(book);
    }

    /**
     * Returns a proper date which can be compared against a value from the GUI.
     * @return the current date with hour,minute,second=00:00:00
     */
    private static Date today()
    {
        Calendar c = GregorianCalendar.getInstance();
        return new GregorianCalendar(c.get(Calendar.YEAR), c.get(Calendar.MONTH), c.get(Calendar.DAY_OF_MONTH))
                .getTime();
    }

}
