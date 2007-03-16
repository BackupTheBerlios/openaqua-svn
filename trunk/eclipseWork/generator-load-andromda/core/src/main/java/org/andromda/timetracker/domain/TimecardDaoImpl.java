// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package org.andromda.timetracker.domain;
/**
 * @see org.andromda.timetracker.domain.Timecard
 */
public class TimecardDaoImpl
    extends org.andromda.timetracker.domain.TimecardDaoBase
{
    /**
     * @see org.andromda.timetracker.domain.TimecardDao#findByCriteria(org.andromda.timetracker.vo.TimecardSearchCriteriaVO)
     */
    protected java.util.List handleFindByCriteria(org.andromda.timetracker.vo.TimecardSearchCriteriaVO criteria)
    {
        // @todo implement public java.util.List handleFindByCriteria(org.andromda.timetracker.vo.TimecardSearchCriteriaVO criteria)
        return null;
}

    /**
     * @see org.andromda.timetracker.domain.TimecardDao#toTimecardSearchCriteriaVO(org.andromda.timetracker.domain.Timecard, org.andromda.timetracker.vo.TimecardSearchCriteriaVO)
     */
    public void toTimecardSearchCriteriaVO(
        org.andromda.timetracker.domain.Timecard source,
        org.andromda.timetracker.vo.TimecardSearchCriteriaVO target)
    {
        // @todo verify behavior of toTimecardSearchCriteriaVO
        super.toTimecardSearchCriteriaVO(source, target);
    }


    /**
     * @see org.andromda.timetracker.domain.TimecardDao#toTimecardSearchCriteriaVO(org.andromda.timetracker.domain.Timecard)
     */
    public org.andromda.timetracker.vo.TimecardSearchCriteriaVO toTimecardSearchCriteriaVO(final org.andromda.timetracker.domain.Timecard entity)
    {
        // @todo verify behavior of toTimecardSearchCriteriaVO
        return super.toTimecardSearchCriteriaVO(entity);
    }


    /**
     * Retrieves the entity object that is associated with the specified value object
     * from the object store. If no such entity object exists in the object store,
     * a new, blank entity is created
     */
    private org.andromda.timetracker.domain.Timecard loadTimecardFromTimecardSearchCriteriaVO(org.andromda.timetracker.vo.TimecardSearchCriteriaVO timecardSearchCriteriaVO)
    {
        // @todo implement loadTimecardFromTimecardSearchCriteriaVO
        throw new java.lang.UnsupportedOperationException("org.andromda.timetracker.domain.loadTimecardFromTimecardSearchCriteriaVO(org.andromda.timetracker.vo.TimecardSearchCriteriaVO) not yet implemented.");

        /* A typical implementation looks like this:
        org.andromda.timetracker.domain.Timecard timecard = this.load(timecardSearchCriteriaVO.getId());
        if (timecard == null)
        {
            timecard = org.andromda.timetracker.domain.Timecard.Factory.newInstance();
        }
        return timecard;
        */
    }

    
    /**
     * @see org.andromda.timetracker.domain.TimecardDao#timecardSearchCriteriaVOToEntity(org.andromda.timetracker.vo.TimecardSearchCriteriaVO)
     */
    public org.andromda.timetracker.domain.Timecard timecardSearchCriteriaVOToEntity(org.andromda.timetracker.vo.TimecardSearchCriteriaVO timecardSearchCriteriaVO)
    {
        // @todo verify behavior of timecardSearchCriteriaVOToEntity
        org.andromda.timetracker.domain.Timecard entity = this.loadTimecardFromTimecardSearchCriteriaVO(timecardSearchCriteriaVO);
        this.timecardSearchCriteriaVOToEntity(timecardSearchCriteriaVO, entity, true);
        return entity;
    }


    /**
     * @see org.andromda.timetracker.domain.TimecardDao#timecardSearchCriteriaVOToEntity(org.andromda.timetracker.vo.TimecardSearchCriteriaVO, org.andromda.timetracker.domain.Timecard)
     */
    public void timecardSearchCriteriaVOToEntity(
        org.andromda.timetracker.vo.TimecardSearchCriteriaVO source,
        org.andromda.timetracker.domain.Timecard target,
        boolean copyIfNull)
    {
        // @todo verify behavior of timecardSearchCriteriaVOToEntity
        super.timecardSearchCriteriaVOToEntity(source, target, copyIfNull);
    }

}