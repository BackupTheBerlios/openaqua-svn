/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    KeyCacheFile

\brief    


\date     $Date: 2006/03/12 19:13:27,62 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   KeyCacheFile_HPP
#define   KeyCacheFile_HPP

class     KeyCacheFile;

class     ACObject;
class     DBIndex;
#include  <sEB_Number.hpp>
#include  <sKeyCacheBase.hpp>
#include  <sPropertyHandle.hpp>
class  KeyCacheFile :public KeyCacheBase
{
protected  :         PropertyHandle                               key_lock;                                                  //
protected  :         PropertyHandle                               indexes;                                                   //
protected  :         PropertyHandle                               entries;                                                   //
protected  :         char                                         keyarea[512];                                              //
protected  :         ACObject                                    *ob_handle;                                                 //
protected  :         int32                                        owner;                                                     

public     :
                     PropertyHandle                              &get_key_lock() { return(key_lock); }
                     PropertyHandle                              &get_indexes() { return(indexes); }
                     PropertyHandle                              &get_entries() { return(entries); }
                     char                                        *get_keyarea() { return(keyarea); }
public     :                                     logical Initialize (EB_Number entnr, DBIndex *db_index, char *keyptr );
public     :                                                             KeyCacheFile (ACObject *obhandle );
public     : virtual                             logical LockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id );
public     :                                     logical Reset ( );
public     : virtual                             logical UnlockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id );
public     : virtual                                                     ~KeyCacheFile ( );
};

#endif
