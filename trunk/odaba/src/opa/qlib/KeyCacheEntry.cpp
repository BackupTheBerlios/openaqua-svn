/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    KeyCacheEntry

\brief    


\date     $Date: 2006/03/12 19:17:39,54 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "KeyCacheEntry"

#include  <popa7.h>
#include  <sKeyCacheEntry.hpp>


/******************************************************************************/
/**
\brief  KeyCacheEntry - 



\param  keyptr -
\param  keylen -
\param  owner_id -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KeyCacheEntry"

                        KeyCacheEntry :: KeyCacheEntry (char *keyptr, int32 keylen, int32 owner_id )
                     :   key_value(NULL),
  owner(owner_id),
  lock_count(0)
{

  if ( keylen > 0 && keyptr )
  {
    key_value = new char[keylen];
    memcpy(key_value,keyptr,keylen);
  }

}

/******************************************************************************/
/**
\brief  Lock - 


\return term - Termination code

\param  owner_id -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical KeyCacheEntry :: Lock (int32 owner_id )
{
  logical                 term = NO;
BEGINSEQ
  if ( owner_id != owner )                           SDBERR(6)

  lock_count++;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Unlock - 


\return term - Termination code

\param  owner_id -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical KeyCacheEntry :: Unlock (int32 owner_id )
{
  logical                 term = NO;
BEGINSEQ
  if ( owner_id != owner )                           SDBERR(6)
  if ( lock_count <= 0 )                             SDBERR(6)
    
  lock_count--;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~KeyCacheEntry - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~KeyCacheEntry"

                        KeyCacheEntry :: ~KeyCacheEntry ( )
{

  if ( key_value )
    delete key_value;
  key_value = NULL;

}


