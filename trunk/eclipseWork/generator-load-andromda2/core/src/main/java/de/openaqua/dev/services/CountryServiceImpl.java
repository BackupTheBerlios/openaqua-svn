// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package de.openaqua.dev.services;

import java.util.Collection;

import de.openaqua.dev.entities.Country;
import de.openaqua.dev.entities.CountryDao;
import de.openaqua.dev.vo.CountryVO;

/**
 * @see de.openaqua.dev.services.CountryService
 */
public class CountryServiceImpl
    extends de.openaqua.dev.services.CountryServiceBase
{

    /**
     * @see de.openaqua.dev.services.CountryService#getAllCountries()
     */
    protected de.openaqua.dev.vo.CountryVO[] handleGetAllCountries()
        throws java.lang.Exception
    {
        // @todo implement protected de.openaqua.dev.vo.CountryVO[] handleGetAllCountries()
    	final Collection collection = getCountryDao().loadAll();
    	getCountryDao().toCountryVOCollection(collection);
    	return (CountryVO[]) collection.toArray();
    }

    /**
     * @see de.openaqua.dev.services.CountryService#getCountriesByIso(java.lang.String)
     */
    protected java.util.List handleGetCountriesByIso(java.lang.String iso)
        throws java.lang.Exception
    {
        // @todo implement protected java.util.List handleGetCountriesByIso(java.lang.String iso)
        return null;
    }

}