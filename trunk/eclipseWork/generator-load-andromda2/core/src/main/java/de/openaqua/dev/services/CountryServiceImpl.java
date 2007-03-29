//license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package de.openaqua.dev.services;

import java.util.Collection;
import java.util.List;

import de.openaqua.dev.entities.Country;
import de.openaqua.dev.vo.CountryVO;

/**
 * @see de.openaqua.dev.services.CountryService
 */
public class CountryServiceImpl
extends de.openaqua.dev.services.CountryServiceBase
{

	/**
	 * @see de.openaqua.dev.services.CountryService#findCountriesByCriteria(de.openaqua.dev.services.CountryCriteria)
	 */
	protected de.openaqua.dev.vo.CountryVO[] handleFindCountriesByCriteria(de.openaqua.dev.services.CountryCriteria criteria)
	throws java.lang.Exception
	{
		List countries=getCountryDao().findByCriteria(criteria);
		getCountryDao().toCountryVOCollection(countries);
		return (CountryVO[]) (countries.toArray(new CountryVO[0]));
	}

	@Override
	protected CountryVO[] handleGetAllCountries() throws Exception {
		Collection entities = getCountryDao().loadAll();
		getCountryDao().toCountryVOCollection(entities);
		return (CountryVO[]) entities.toArray(new CountryVO[0]);
	}

}