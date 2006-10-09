/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_KeyLockInstance

\brief    Key lock instance
          A  key  lock  instance  defines  the key, that is locked in the index.
          Keys  might be locked  by different users,  which are identified by an
          owner  identifier. Keys  can be  locked multiple,  but each key can be
          locked, however, only by one owner (workspace or database session).

\date     $Date: 2006/03/13 21:30:09,23 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_KeyLockInstance_HPP
#define   SDB_KeyLockInstance_HPP

class     SDB_KeyLockInstance;

#pragma pack(8)

class  SDB_KeyLockInstance
{
public     :         char                                         value[512];                                                // Key value
public     :         int64                                        owner;                                                     // Owner of the key
public     :         int32                                        lock_count;                                                // Lock count

public     :
};

#pragma pack()
#endif
