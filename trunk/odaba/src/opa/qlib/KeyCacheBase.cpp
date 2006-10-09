/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    KeyCacheBase

\brief    


\date     $Date: 2006/03/12 19:17:39,35 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "KeyCacheBase"

#include  <popa7.h>
#include  <sDBIndex.hpp>
#include  <sKeyCacheBase.hpp>


/******************************************************************************/
/**
\brief  KeyCacheBase - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KeyCacheBase"

                        KeyCacheBase :: KeyCacheBase ( )
{



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

logical KeyCacheBase :: LockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id )
{


  return(NO);
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

logical KeyCacheBase :: UnlockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  ~KeyCacheBase - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~KeyCacheBase"

                        KeyCacheBase :: ~KeyCacheBase ( )
{



}


