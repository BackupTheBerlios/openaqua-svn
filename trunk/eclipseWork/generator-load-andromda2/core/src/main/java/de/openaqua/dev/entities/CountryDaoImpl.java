// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package de.openaqua.dev.entities;
/**
 * @see de.openaqua.dev.entities.Country
 */
public class CountryDaoImpl
    extends de.openaqua.dev.entities.CountryDaoBase
{
    /**
     * @see de.openaqua.dev.entities.CountryDao#toCountryVO(de.openaqua.dev.entities.Country, de.openaqua.dev.vo.CountryVO)
     */
    public void toCountryVO(
        de.openaqua.dev.entities.Country source,
        de.openaqua.dev.vo.CountryVO target)
    {
        // @todo verify behavior of toCountryVO
        super.toCountryVO(source, target);
        // WARNING! No conversion for target.phoneFormat (can't convert source.getPhoneFormat():de.openaqua.dev.entities.PhoneFormat to java.lang.String
    }


    /**
     * @see de.openaqua.dev.entities.CountryDao#toCountryVO(de.openaqua.dev.entities.Country)
     */
    public de.openaqua.dev.vo.CountryVO toCountryVO(final de.openaqua.dev.entities.Country entity)
    {
        // @todo verify behavior of toCountryVO
        return super.toCountryVO(entity);
    }


    /**
     * Retrieves the entity object that is associated with the specified value object
     * from the object store. If no such entity object exists in the object store,
     * a new, blank entity is created
     */
    private de.openaqua.dev.entities.Country loadCountryFromCountryVO(de.openaqua.dev.vo.CountryVO countryVO)
    {
        // @todo implement loadCountryFromCountryVO
        throw new java.lang.UnsupportedOperationException("de.openaqua.dev.entities.loadCountryFromCountryVO(de.openaqua.dev.vo.CountryVO) not yet implemented.");

        /* A typical implementation looks like this:
        de.openaqua.dev.entities.Country country = this.load(countryVO.getId());
        if (country == null)
        {
            country = de.openaqua.dev.entities.Country.Factory.newInstance();
        }
        return country;
        */
    }

    
    /**
     * @see de.openaqua.dev.entities.CountryDao#countryVOToEntity(de.openaqua.dev.vo.CountryVO)
     */
    public de.openaqua.dev.entities.Country countryVOToEntity(de.openaqua.dev.vo.CountryVO countryVO)
    {
        // @todo verify behavior of countryVOToEntity
        de.openaqua.dev.entities.Country entity = this.loadCountryFromCountryVO(countryVO);
        this.countryVOToEntity(countryVO, entity, true);
        return entity;
    }


    /**
     * @see de.openaqua.dev.entities.CountryDao#countryVOToEntity(de.openaqua.dev.vo.CountryVO, de.openaqua.dev.entities.Country)
     */
    public void countryVOToEntity(
        de.openaqua.dev.vo.CountryVO source,
        de.openaqua.dev.entities.Country target,
        boolean copyIfNull)
    {
        // @todo verify behavior of countryVOToEntity
        super.countryVOToEntity(source, target, copyIfNull);
    }

    /**
     * @see de.openaqua.dev.entities.CountryDao#toCountryVOLookupCriteria(de.openaqua.dev.entities.Country, de.openaqua.dev.vo.CountryVOLookupCriteria)
     */
    public void toCountryVOLookupCriteria(
        de.openaqua.dev.entities.Country source,
        de.openaqua.dev.vo.CountryVOLookupCriteria target)
    {
        // @todo verify behavior of toCountryVOLookupCriteria
        super.toCountryVOLookupCriteria(source, target);
    }


    /**
     * @see de.openaqua.dev.entities.CountryDao#toCountryVOLookupCriteria(de.openaqua.dev.entities.Country)
     */
    public de.openaqua.dev.vo.CountryVOLookupCriteria toCountryVOLookupCriteria(final de.openaqua.dev.entities.Country entity)
    {
        // @todo verify behavior of toCountryVOLookupCriteria
        return super.toCountryVOLookupCriteria(entity);
    }


    /**
     * Retrieves the entity object that is associated with the specified value object
     * from the object store. If no such entity object exists in the object store,
     * a new, blank entity is created
     */
    private de.openaqua.dev.entities.Country loadCountryFromCountryVOLookupCriteria(de.openaqua.dev.vo.CountryVOLookupCriteria countryVOLookupCriteria)
    {
        de.openaqua.dev.entities.Country country = this.load(countryVOLookupCriteria.getId());
        if (country == null)
        {
            country = de.openaqua.dev.entities.Country.Factory.newInstance();
        }
        return country;
    }

    
    /**
     * @see de.openaqua.dev.entities.CountryDao#countryVOLookupCriteriaToEntity(de.openaqua.dev.vo.CountryVOLookupCriteria)
     */
    public de.openaqua.dev.entities.Country countryVOLookupCriteriaToEntity(de.openaqua.dev.vo.CountryVOLookupCriteria countryVOLookupCriteria)
    {
        // @todo verify behavior of countryVOLookupCriteriaToEntity
        de.openaqua.dev.entities.Country entity = this.loadCountryFromCountryVOLookupCriteria(countryVOLookupCriteria);
        this.countryVOLookupCriteriaToEntity(countryVOLookupCriteria, entity, true);
        return entity;
    }


    /**
     * @see de.openaqua.dev.entities.CountryDao#countryVOLookupCriteriaToEntity(de.openaqua.dev.vo.CountryVOLookupCriteria, de.openaqua.dev.entities.Country)
     */
    public void countryVOLookupCriteriaToEntity(
        de.openaqua.dev.vo.CountryVOLookupCriteria source,
        de.openaqua.dev.entities.Country target,
        boolean copyIfNull)
    {
        // @todo verify behavior of countryVOLookupCriteriaToEntity
        super.countryVOLookupCriteriaToEntity(source, target, copyIfNull);
    }

}