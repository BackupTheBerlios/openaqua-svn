/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    KeyCacheFile

\brief    


\date     $Date: 2006/03/12 19:17:39,70 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "KeyCacheFile"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sDBIndex.hpp>
#include  <sLACObject.hpp>
#include  <sSDB_KeyLockInstance.hpp>
#include  <sKeyCacheFile.hpp>


/******************************************************************************/
/**
\brief  Initialize - 


\return term - Termination code

\param  entnr -
\param  db_index -
\param  keyptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical KeyCacheFile :: Initialize (EB_Number entnr, DBIndex *db_index, char *keyptr )
{
  kcb                    *kcbptr;
  int32                   keylen;
  logical                 term = NO;
BEGINSEQ
  if ( !(kcbptr = db_index->get_key_def()) )         ERROR
  if ( !(keylen = kcbptr->GetKeyLength()) )          ERROR

  if ( !indexes.Provide(Key((char *)&entnr)) )       SDBERR(99)
  
  memset(keyarea,0,sizeof(keyarea));
  memcpy(keyarea,keyptr,MIN(keylen,sizeof(keyarea)));


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  KeyCacheFile - 



\param  obhandle - Database Object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KeyCacheFile"

                        KeyCacheFile :: KeyCacheFile (ACObject *obhandle )
                     : KeyCacheBase (),
  key_lock(),
  indexes(),
  entries(),
  keyarea(),
  ob_handle(NULL)
{
  PropertyHandle          blank_key("");
BEGINSEQ
  if ( !(ob_handle = obhandle->GetLocalACObject()->ReserveGlobalObject()) )
                                                     SDBERR(99)
  DBObjectHandle          dbh(ob_handle);

  key_lock.Open(dbh,"SDB_KeyLock",PI_Update);
  indexes.Open(&key_lock,"collections");
  entries.Open(&indexes,"key_locks");

  key_lock.Provide(blank_key);
  PH(&key_lock,last_use_id)
  owner = last_use_id.GetInt() + 1;
  last_use_id = owner;
  key_lock.Save();

  obhandle->GetLocalACObject()->ReleaseGlobalObject();
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  LockKey - 


\return term - Termination code

\param  entnr -
\param  db_index -
\param  keyptr -
\param  owner_id -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockKey"

logical KeyCacheFile :: LockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id )
{
  SDB_KeyLockInstance    *kl_entry;
  logical                 term = NO;
BEGINSEQ
  if ( Initialize(entnr,db_index,keyptr) )           ERROR

  if ( !(kl_entry = (SDB_KeyLockInstance *)entries.Provide(keyarea).GetData()) )
                                                     SDBERR(99)
  if ( !kl_entry->owner )
    kl_entry->owner = owner;
  else
    if ( kl_entry->owner != owner )                  SDBERR(6)
  
  kl_entry->lock_count++;
  entries.Modify();
  entries.Save();
RECOVER
  term = YES;
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  Reset - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical KeyCacheFile :: Reset ( )
{
  SDB_KeyLockInstance    *kl_entry;
  int32                   i = 0;
  int32                   j = 0;
  logical                 term = NO;
  while ( indexes.Get(i++) )
  {
    j = 0;
    while ( kl_entry = (SDB_KeyLockInstance *)entries.Get(j++).GetData() )
      if ( kl_entry->owner == owner )
      {
        entries.Delete(AUTO);
        j--;
      }
      
    if ( !entries.GetCount() )
    {
      indexes.Delete(AUTO);
      i--;
    }
  }

  return(term);
}

/******************************************************************************/
/**
\brief  UnlockKey - 


\return term - Termination code

\param  entnr -
\param  db_index -
\param  keyptr -
\param  owner_id -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockKey"

logical KeyCacheFile :: UnlockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id )
{
  SDB_KeyLockInstance    *kl_entry;
  logical                 term = NO;
BEGINSEQ
  if ( Initialize(entnr,db_index,keyptr) )           ERROR

  if ( !(kl_entry = (SDB_KeyLockInstance *)entries.Get(keyarea).GetData()) )
                                                     SDBERR(99)
  if ( kl_entry->owner != owner )                    SDBERR(6)
  
  if ( --kl_entry->lock_count > 0 )
  {
    entries.Modify();
    entries.Save();
  }
  else
  {
    entries.Delete(AUTO);
    if ( entries.GetCount() <= 0 )
      indexes.Delete(AUTO);
  }
RECOVER
  term = YES;
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  ~KeyCacheFile - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~KeyCacheFile"

                        KeyCacheFile :: ~KeyCacheFile ( )
{

  Reset();

}


