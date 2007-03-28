// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package de.openaqua.dev.services;

import java.util.Collection;

import org.apache.log4j.Logger;
import org.hibernate.property.Getter;

import de.openaqua.dev.entities.Country;
import de.openaqua.dev.entities.CountryDao;
import de.openaqua.dev.vo.CountryVO;
import de.openaqua.dev.vo.CountryVOLookupCriteria;

/**
 * @see de.openaqua.dev.services.CountryService
 */
public class CountryServiceImpl
    extends de.openaqua.dev.services.CountryServiceBase
{
	Logger logger = Logger.getRootLogger();

    /**
     * @see de.openaqua.dev.services.CountryService#getAllCountries()
     */
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
    	logger.info("Look for ISO "+iso);
    	CountryVOLookupCriteria crit = new CountryVOLookupCriteria();
    	crit.setIso(iso);
        Country c = getCountryDao().countryVOLookupCriteriaToEntity(crit);
        logger.info("Found country with id "+c.getId());
        return getCountryDao().toCountryVO(c);
    }

}