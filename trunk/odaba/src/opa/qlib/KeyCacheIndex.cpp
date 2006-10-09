/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    KeyCacheIndex

\brief    


\date     $Date: 2006/03/12 19:17:40,00 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "KeyCacheIndex"

#include  <popa7.h>
#include  <sDBIndex.hpp>
#include  <sKeyCacheEntry.hpp>
#include  <sKeyCacheIndex.hpp>


/******************************************************************************/
/**
\brief  GetCount - 


\return count -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 KeyCacheIndex :: GetCount ( )
{

  return ( entries.GetCount() );

}

/******************************************************************************/
/**
\brief  GetEntry - 


\return kc_entry -

\param  keyptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntry"

KeyCacheEntry *KeyCacheIndex :: GetEntry (char *keyptr )
{
  KeyCacheEntry          *kc_entry = NULL;
  entries.GoTop();
  while ( kc_entry = entries.GetNext() )
    if ( !index->get_key_def()->CompareKeys(keyptr,kc_entry->get_key_value(),CMP_KK) )
      break;
  return(kc_entry);
}

/******************************************************************************/
/**
\brief  KeyCacheIndex - 



\param  entnr -
\param  db_index -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KeyCacheIndex"

                        KeyCacheIndex :: KeyCacheIndex (EB_Number entnr, DBIndex *db_index )
                     : ebsnum(entnr),
  index(db_index),
  entries()
{

  keylen = index->get_key_def()->GetKeyLength();

}

/******************************************************************************/
/**
\brief  LockEntry - 


\return term - Termination code

\param  keyptr -
\param  owner_id -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockEntry"

logical KeyCacheIndex :: LockEntry (char *keyptr, int32 owner_id )
{
  KeyCacheEntry          *kc_entry = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !(kc_entry = GetEntry(keyptr)) )
  {
    kc_entry = new KeyCacheEntry(keyptr,keylen,owner_id);
    entries.AddTail(kc_entry);
  }

  if ( kc_entry->Lock(owner_id) )                    ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  UnlockEntry - 


\return term - Termination code

\param  keyptr -
\param  owner_id -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockEntry"

logical KeyCacheIndex :: UnlockEntry (char *keyptr, int32 owner_id )
{
  KeyCacheEntry          *kc_entry = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !(kc_entry = GetEntry(keyptr)) )              SDBERR(6)
  
  if ( kc_entry->Unlock(owner_id) )                  ERROR

  if ( !kc_entry->get_lock_count() ) 
  {
    entries.Remove(kc_entry);
    delete kc_entry;
  } 

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~KeyCacheIndex - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~KeyCacheIndex"

                        KeyCacheIndex :: ~KeyCacheIndex ( )
{
  KeyCacheEntry        *kc_entry;
  while ( kc_entry = entries.RemoveTail() )
    delete kc_entry;

}


