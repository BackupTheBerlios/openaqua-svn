/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    KeyCache

\brief    


\date     $Date: 2006/03/12 19:17:39,00 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "KeyCache"

#include  <popa7.h>
#include  <sBinTree.hpp>
#include  <sDBIndex.hpp>
#include  <sKeyCacheIndex.hpp>
#include  <sKeyCache.hpp>


/******************************************************************************/
/**
\brief  GetIndex - 


\return kc_index -
-------------------------------------------------------------------------------
\brief i0


\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndex"

KeyCacheIndex *KeyCache :: GetIndex (EB_Number entnr )
{

  return( (KeyCacheIndex *) Get((char *)&entnr,YES) );

}

/******************************************************************************/
/**
\brief i01


\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndex"

KeyCacheIndex *KeyCache :: GetIndex (int32 indx0 )
{

  return( (KeyCacheIndex *) Get(indx0) );

}

/******************************************************************************/
/**
\brief  ILock

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ILock"

logical KeyCache :: ILock ( )
{

  return ( tree->Lock() );

}

/******************************************************************************/
/**
\brief  IUnlock

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IUnlock"

logical KeyCache :: IUnlock ( )
{

  return ( tree->Unlock() );

}

/******************************************************************************/
/**
\brief  KeyCache - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KeyCache"

                        KeyCache :: KeyCache ( )
                     : KeyCacheBase(),
BTIterator (NULL),
  tree(NULL)
{

  tree = new BinTree(sizeof(KeyCacheIndex),offsetof(KeyCacheIndex,ebsnum),sizeof(EB_Number),'I',256);
  SetTree(tree);

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

logical KeyCache :: LockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id )
{
  KeyCacheIndex          *kc_index = NULL;
  logical                 term = NO;
BEGINSEQ
  ILock();
  if ( !(kc_index = GetIndex(entnr)) )
  {
    kc_index = new KeyCacheIndex(entnr,db_index);
    tree->CreateEntry((void *)kc_index);
  }
  
  if ( kc_index->LockEntry(keyptr,owner_id) )        ERROR

RECOVER
  term = YES;
ENDSEQ
  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveIndex - 



\param  kc_index -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveIndex"

void KeyCache :: RemoveIndex (KeyCacheIndex *kc_index )
{

  tree->DeleteEntry((void *)kc_index);
  delete kc_index;


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

logical KeyCache :: UnlockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id )
{
  KeyCacheIndex          *kc_index = NULL;
  logical                 term = NO;
BEGINSEQ
  ILock();
  if ( !(kc_index = GetIndex(entnr)) )               SDBERR(6)
  
  if ( kc_index->UnlockEntry(keyptr,owner_id) )      ERROR
  
  if ( !kc_index->GetCount() )
    RemoveIndex(kc_index);

RECOVER
  term = YES;
ENDSEQ
  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  ~KeyCache - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~KeyCache"

                        KeyCache :: ~KeyCache ( )
{
  KeyCacheIndex          *kc_index = NULL;
  while ( kc_index = GetIndex(0) )
    RemoveIndex(kc_index);
  
  delete tree;
  tree = NULL;

}


