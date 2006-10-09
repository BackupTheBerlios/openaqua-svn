/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    HashTable

\brief    


\date     $Date: 2006/03/12 19:21:42,65 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "HashTable"

#include  <pdefault.h>
#include  <sHashEntry.hpp>
#include  <sRecycler.hpp>
#include  <sHashTable.hpp>

Recycler               *HashTable::recycler= 0;

/******************************************************************************/
/**
\brief  Add - 



\param  pvoidKey -
\param  pvoidItem -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void HashTable :: Add (void *pvoidKey, void *pvoidItem )
{
  HashEntry  *e;
  uint32      hv;
  lock.ILock();

  if ( !table )
    Rehash(len);

  count++;

  if ( autoRehash && count > len / 2 )
    Rehash(len * 2 - 1);

  hv = DoHash(pvoidKey) % len;

  if ( !(e= recycler->Take()) ) 
    e = new HashEntry;

  e->key    = pvoidKey;
  e->item   = pvoidItem;
  DoAdd(&e->key,&e->item);
  e->next   = (HashEntry *)table[hv];
  table[hv] = e;
lock.IUnlock();
}

/******************************************************************************/
/**
\brief  Clear - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

void HashTable :: Clear ( )
{

  if ( table )
  {
    freeTable(table,len,YES);
    table = 0;
  }

  if ( autoRehash ) 
    len = 7;

}

/******************************************************************************/
/**
\brief  Delete

\return term - Success

\param  pvoidKey -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical HashTable :: Delete (void *pvoidKey )
{
  HashEntry  **e;
  HashEntry   *d;
  uint32       hv;
  logical      term = NO;
BEGINSEQ
  lock.ILock();

  if ( !table )                                         ERROR

  hv = DoHash(pvoidKey) % len;
  e  = (HashEntry **)&table[hv];

  while ( *e )
  {
    if ( DoCompare(pvoidKey,(*e)->key) == 0 ) 
    {
      d  = *e;
      DoDelete(d->key,d->item);
      *e = d->next;
      recycler->Add(d);
      count--;
      if ( autoRehash && count < len / 4 ) 
        Rehash((len + 1) / 2);
      LEAVESEQ
    }
    e = &(*e)->next;
  }

  ERROR
RECOVER
  term = YES;
ENDSEQ
  lock.IUnlock();
  return term;
}

/******************************************************************************/
/**
\brief  DoAdd


\param  ppvoidKey -
\param  ppvoidItem -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAdd"

void HashTable :: DoAdd (void **ppvoidKey, void **ppvoidItem )
{



}

/******************************************************************************/
/**
\brief  DoCompare

\return cmpval - Comparision result

\param  pvoidKey1 -
\param  pvoidKey2 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoCompare"

int HashTable :: DoCompare (void *pvoidKey1, void *pvoidKey2 )
{

  return (char *)pvoidKey1 - (char *)pvoidKey2;

}

/******************************************************************************/
/**
\brief  DoDelete


\param  pvoidKey -
\param  pvoidItem -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoDelete"

void HashTable :: DoDelete (void *pvoidKey, void *pvoidItem )
{



}

/******************************************************************************/
/**
\brief  DoHash

\return index -

\param  pvoidKey -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoHash"

uint32 HashTable :: DoHash (void *pvoidKey )
{

  return (uint32)pvoidKey;

}

/******************************************************************************/
/**
\brief  Find - 


\return pData -

\param  pvoidKey -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Find"

void *HashTable :: Find (void *pvoidKey )
{
  HashEntry   *e;
  uint32       hv;
  void        *it = 0;

BEGINSEQ
  lock.ILock();

  if ( !table )                                         ERROR

  hv = DoHash(pvoidKey) % len;
  e  = (HashEntry *)table[hv];

  while ( e )
  {
    if ( DoCompare(pvoidKey,e->key) == 0 ) 
    {
      it = e->item;
      LEAVESEQ
    }
    e = e->next;
  }
RECOVER

ENDSEQ
  lock.IUnlock();
  return it;
}

/******************************************************************************/
/**
\brief  HashTable

\return term - Success
-------------------------------------------------------------------------------
\brief i0


\param  len -
\param  fAutoRehash -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HashTable"

                        HashTable :: HashTable (size_t len, logical fAutoRehash )
                     :   len(len),
  table(0),
  count(0),
  autoRehash(fAutoRehash),
  lock(NO)
{

  if ( !recycler ) 
    recycler = new Recycler();

}

/******************************************************************************/
/**
\brief i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HashTable"

                        HashTable :: HashTable ( )
                     : table(0),
  len(0),
  count(0),
  autoRehash(YES),
  lock(NO)
{

if( !recycler ) recycler= new Recycler();

}

/******************************************************************************/
/**
\brief  Rehash


\param  len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Rehash"

void HashTable :: Rehash (size_t len )
{
  HashEntry    **hes;
  HashEntry     *he;
  void         **otable;
  uint32         olen;
  uint32         oleft;
  lock.ILock();

  if ( len < 7 ) 
    len = 7;

  olen      = this->len;
  otable    = this->table;
  count     = 0;
  this->len = len;
  table     = new void*[len];
  memset(table,0,len * sizeof(void *));

  if ( otable )
  {
    hes   = (HashEntry **)otable;
    oleft = olen;
    for ( ; oleft > 0; oleft--, hes++ )
    {
      he = *hes;
      while ( he )
      {
        Add(he->key,he->item);
        he = he->next;
      }
    }
    freeTable(otable,olen,NO);
  }

  lock.IUnlock();
}

/******************************************************************************/
/**
\brief  Take

\return pData -

\param  pvoidKey -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Take"

void *HashTable :: Take (void *pvoidKey )
{
  HashEntry    **e;
  HashEntry     *d;
  uint32         hv;
  void          *it = 0;
BEGINSEQ
  lock.ILock();

  if ( !table )                                         ERROR

  hv = DoHash( pvoidKey ) % len;
  e  = (HashEntry **)&table[hv];

  while ( *e )
  {
    if ( DoCompare(pvoidKey,(*e)->key) == 0 ) 
    {
      d  = *e;
      it = d->item;
      DoDelete(it,0);
      *e = d->next;
      recycler->Add(d);
      count--;
      if ( autoRehash && count < len / 4 ) 
        Rehash((len + 1) / 2);
      LEAVESEQ
    }
    e = &(*e)->next;
  }
RECOVER

ENDSEQ
  lock.IUnlock();
  return it;
}

/******************************************************************************/
/**
\brief  _TEST_

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "_TEST_"

logical __cdecl HashTable :: _TEST_ ( )
{
  HashTable           *a    = new HashTable;
  int                  i;
  int                  j;
  logical              term = NO;
BEGINSEQ
  for ( j = 0; j < 100; j++ )
  {
    for ( i = 1; i < 10000; i++ )
      a->Add((void *)i,(void *)i);
    
    for ( i = 1; i < 10000; i++ )
      if ( a->Delete((void *)i) )                    ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  freeTable


\param  ppvoidTable -
\param  len -
\param  fDelete -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "freeTable"

void HashTable :: freeTable (void **ppvoidTable, size_t len, logical fDelete )
{
  HashEntry   **hes  = (HashEntry **)ppvoidTable;
  HashEntry    *he;
  HashEntry    *d;
  uint32        left = len;

  for ( ; left > 0; left--, hes++ )
  {
    he = *hes;
    while ( he )
    {
      if ( fDelete ) 
        DoDelete(he->key,he->item);
      d  = he;
      he = he->next;
      recycler->Add(d);
    }
  }
  
  delete[] ppvoidTable;


}

/******************************************************************************/
/**
\brief  ~HashTable

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~HashTable"

                        HashTable :: ~HashTable ( )
{

  Clear();

}


