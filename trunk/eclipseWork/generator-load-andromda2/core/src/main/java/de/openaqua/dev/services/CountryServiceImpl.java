// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package de.openaqua.dev.services;

import java.util.Collection;

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
     * @todo TRANSFORM_NONE?
     * @todo dao selbst erzeugen???
     */
    @SuppressWarnings("unchecked")
	protected de.openaqua.dev.vo.CountryVO[] handleGetAllCountries()
        throws java.lang.Exception
    {
    	final Collection<de.openaqua.dev.entities.Country> collection = getCountryDao().loadAll(CountryDao.TRANSFORM_COUNTRYVO);
    	return collection.toArray(new CountryVO[0]);
    }

    /**
     * @see de.openaqua.dev.services.CountryService#getCountryByIso(java.lang.String)
     */
    protected de.openaqua.dev.vo.CountryVO handleGetCountryByIso(java.lang.String iso)
        throws java.lang.Exception
    {
        // @todo implement protected de.openaqua.dev.vo.CountryVO handleGetCountryByIso(java.lang.String iso)
        return null;
    }

}