// license-header java merge-point
/**
 * This is only generated once! It will never be overwritten.
 * You can (and have to!) safely modify it by hand.
 */
package org.andromda.timetracker.domain;
/**
 * @see org.andromda.timetracker.domain.User
 */
public class UserDaoImpl
    extends org.andromda.timetracker.domain.UserDaoBase
{
    /**
     * @see org.andromda.timetracker.domain.UserDao#toUserVO(org.andromda.timetracker.domain.User, org.andromda.timetracker.vo.UserVO)
     */
    public void toUserVO(
        org.andromda.timetracker.domain.User source,
        org.andromda.timetracker.vo.UserVO target)
    {
        // @todo verify behavior of toUserVO
        super.toUserVO(source, target);
    }


    /**
     * @see org.andromda.timetracker.domain.UserDao#toUserVO(org.andromda.timetracker.domain.User)
     */
    public org.andromda.timetracker.vo.UserVO toUserVO(final org.andromda.timetracker.domain.User entity)
    {
        // @todo verify behavior of toUserVO
        return super.toUserVO(entity);
    }


    /**
     * Retrieves the entity object that is associated with the specified value object
     * from the object store. If no such entity object exists in the object store,
     * a new, blank entity is created
     */
    private org.andromda.timetracker.domain.User loadUserFromUserVO(org.andromda.timetracker.vo.UserVO userVO)
    {
        // @todo implement loadUserFromUserVO
        throw new java.lang.UnsupportedOperationException("org.andromda.timetracker.domain.loadUserFromUserVO(org.andromda.timetracker.vo.UserVO) not yet implemented.");

        /* A typical implementation looks like this:
        org.andromda.timetracker.domain.User user = this.load(userVO.getId());
        if (user == null)
        {
            user = org.andromda.timetracker.domain.User.Factory.newInstance();
        }
        return user;
        */
    }

    
    /**
     * @see org.andromda.timetracker.domain.UserDao#userVOToEntity(org.andromda.timetracker.vo.UserVO)
     */
    public org.andromda.timetracker.domain.User userVOToEntity(org.andromda.timetracker.vo.UserVO userVO)
    {
        // @todo verify behavior of userVOToEntity
        org.andromda.timetracker.domain.User entity = this.loadUserFromUserVO(userVO);
        this.userVOToEntity(userVO, entity, true);
        return entity;
    }


    /**
     * @see org.andromda.timetracker.domain.UserDao#userVOToEntity(org.andromda.timetracker.vo.UserVO, org.andromda.timetracker.domain.User)
     */
    public void userVOToEntity(
        org.andromda.timetracker.vo.UserVO source,
        org.andromda.timetracker.domain.User target,
        boolean copyIfNull)
    {
        // @todo verify behavior of userVOToEntity
        super.userVOToEntity(source, target, copyIfNull);
    }

}