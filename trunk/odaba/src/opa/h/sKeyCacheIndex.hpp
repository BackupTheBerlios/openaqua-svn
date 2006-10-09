/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    KeyCacheIndex

\brief    


\date     $Date: 2006/03/12 19:13:27,93 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   KeyCacheIndex_HPP
#define   KeyCacheIndex_HPP

class     KeyCacheIndex;

#ifndef   DLL_KeyCacheEntry_HPP
#define   DLL_KeyCacheEntry_HPP
#include  <sKeyCacheEntry.hpp>
#include  <sDLL.h>
#endif
class     DBIndex;
class     KeyCacheEntry;
#include  <sEB_Number.hpp>
class  KeyCacheIndex
{
public     :         EB_Number                                    ebsnum;                                                    //
protected  :         DBIndex                                     *index;                                                     //
protected  :         int32                                        keylen;                                                    //
protected  :         DLL(KeyCacheEntry)                           entries;                                                   //

public     :
                     DBIndex                                     *get_index() { return(index); }
                     int32                                        get_keylen() { return(keylen); }
                     DLL(KeyCacheEntry)                          &get_entries() { return(entries); }
public     :                                     int32 GetCount ( );
public     :                                     KeyCacheEntry *GetEntry (char *keyptr );
public     :                                                             KeyCacheIndex (EB_Number entnr, DBIndex *db_index );
public     :                                     logical LockEntry (char *keyptr, int32 owner_id );
public     :                                     logical UnlockEntry (char *keyptr, int32 owner_id );
public     :                                                             ~KeyCacheIndex ( );
};

#endif
