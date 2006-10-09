/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    KeyCacheEntry

\brief    


\date     $Date: 2006/03/12 19:13:27,45 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   KeyCacheEntry_HPP
#define   KeyCacheEntry_HPP

class     KeyCacheEntry;

#include  <sEB_Number.hpp>
class  KeyCacheEntry
{
public     :         EB_Number                                    ebsnum;                                                    //
protected  :         char                                        *key_value;                                                 //
protected  :         int32                                        owner;                                                     //
protected  :         int32                                        lock_count;                                                //

public     :
                     char                                        *get_key_value() { return(key_value); }
                     int32                                        get_owner() { return(owner); }
                     int32                                        get_lock_count() { return(lock_count); }
public     :                                                             KeyCacheEntry (char *keyptr, int32 keylen, int32 owner_id );
public     :                                     logical Lock (int32 owner_id );
public     :                                     logical Unlock (int32 owner_id );
public     :                                                             ~KeyCacheEntry ( );
};

#endif
