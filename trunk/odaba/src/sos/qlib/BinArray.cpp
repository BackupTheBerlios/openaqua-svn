/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    BinArray



\date     $Date: 2006/05/28 16:18:07,01 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "BinArray"

#include  <pdefault.h>
#include  <sBinArray.hpp>
#include  <sBinArrayIdxEntry.hpp>
#include  <sBinArrayObjEntry.hpp>
#include  <sBinSArrayObjEntry.hpp>
#include  <sThreadEntry.hpp>
#include  <sBinArray.hpp>


/******************************************************************************/
/**
\brief  BinArray

-------------------------------------------------------------------------------
\brief  i0


\param  size
\param  blockcount - 
\param  level_num
\param  autoreorg - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BinArray"

     BinArray :: BinArray (uint16 size, uint16 blockcount, int32 level_num, logical autoreorg )
                     : BinSArray (size,blockcount,level_num,autoreorg),
  hight(8),
  updated_entries(),
  last_used(0),
  unused_entries(0),
  first_free_entry(NULL),
  last_free_entry(NULL),
  last_reorg(0)

{
  obj_entry_pool.set_bin_array(this);
  idx_entry_pool.set_bin_array(this);
}

/******************************************************************************/
/**
\brief  i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BinArray"

     BinArray :: BinArray ( )
                     : BinSArray (),
  hight(8),
  updated_entries(),
  last_used(0),
  unused_entries(0),
  first_free_entry(NULL),
  last_free_entry(NULL),
  last_reorg(0)
{
}

/******************************************************************************/
/**
\brief  Clear


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

void BinArray :: Clear ( )
{

  ILock();
  
  BinSArray::Clear();
  
  Reorganize(ULONGMAX);
  last_reorg = 0;
  
  IUnlock();

}

/******************************************************************************/
/**
\brief  Flush

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Flush"

logical BinArray :: Flush ( )
{
  BinArrayObjEntry       *object_entry;
  ILock();
  
  while ( object_entry = updated_entries.RemoveHead() )
    StoreObjEntry(this,object_entry);

  IUnlock();

  return(NO);
}

/******************************************************************************/
/**
\brief  FreeEntry

\return object_entry

\param  entry_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FreeEntry"

BinArrayObjEntry *BinArray :: FreeEntry (uint64 entry_index )
{
  BinArrayObjEntry       *object_entry;

  ILock();
  
  if ( object_entry = ProvideEntryIntern(entry_index,NO) )
    if ( !WaitForEntry(object_entry) ) // vielleicht müssen wir noch den use_count mit abfragen (!=0) 5.2.2003
      FreeObjEntry(object_entry);
  
  IUnlock();

  return(object_entry);
}

/******************************************************************************/
/**
\brief  FreeObjEntry


\param  obj_entry
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FreeObjEntry"

void BinArray :: FreeObjEntry (BinSArrayObjEntry *obj_entry )
{

  ((BinArrayObjEntry *)obj_entry)->ResetUseCount();
  RegUnusedEntry((BinArrayObjEntry *)obj_entry);


}

/******************************************************************************/
/**
\brief  GetNext

\return ba_entry

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNext"

BinArrayObjEntry *BinArray :: GetNext ( )
{
  BinArrayObjEntry   *ba_entry = NULL;
BEGINSEQ
  while ( ba_entry = (BinArrayObjEntry *)obj_entry_pool.GetNext() )
    if ( ba_entry->get_use_count() > 0 )               LEAVESEQ
ENDSEQ
  return(ba_entry);
}

/******************************************************************************/
/**
\brief  GoTop


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GoTop"

void BinArray :: GoTop ( )
{

  obj_entry_pool.GoTop();

}

/******************************************************************************/
/**
\brief  InitObjEntry


\param  obj_entry
\param  entry_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitObjEntry"

void BinArray :: InitObjEntry (BinSArrayObjEntry *obj_entry, uint64 entry_index )
{

  ((BinArrayObjEntry *)obj_entry)->SetIndex(entry_index);


}

/******************************************************************************/
/**
\brief  Lock

\return term - Success

\param  entry_index - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical BinArray :: Lock (uint64 entry_index, logical wait )
{
  BinArrayObjEntry       *object_entry;
  logical                 term = NO;
  if ( object_entry = ProvideEntry(entry_index,YES) )
    term = object_entry->Lock(this,wait);
  return(term);
}

/******************************************************************************/
/**
\brief  LockInternal

\return term - Success

\param  entry_index - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockInternal"

logical BinArray :: LockInternal (uint64 entry_index, logical wait )
{
  BinArrayObjEntry       *object_entry;
  logical                 term = NO;
  if ( object_entry = ProvideEntry(entry_index,YES) )
    term = object_entry->LockInternal(this,wait);
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideEntry

\return object_entry

\param  entry_index - 
\param  create - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideEntry"

BinArrayObjEntry *BinArray :: ProvideEntry (uint64 entry_index, logical create )
{
  BinSArrayObjEntry  *obj_entry;
  BinArrayObjEntry   *object_entry = NULL;
  logical             lock = YES;
BEGINSEQ
  ILock();
  
  last_used++;
  
  if ( !(obj_entry = BinSArray::ProvideEntry(entry_index,create)) )
                                                     ERROR
  object_entry = (BinArrayObjEntry *)obj_entry;
  
  if ( object_entry->get_use_count() )
  {
    if ( WaitForEntry(object_entry) )                ERROR
  }
  else
    RegUnusedEntry(object_entry);

RECOVER
  object_entry = NULL;
ENDSEQ
  if ( lock )
    IUnlock();
  return(object_entry);
}

/******************************************************************************/
/**
\brief  ProvideEntryIntern

\return object_entry

\param  entry_index - 
\param  create - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideEntryIntern"

BinArrayObjEntry *BinArray :: ProvideEntryIntern (uint64 entry_index, logical create )
{
  BinSArrayObjEntry  *obj_entry;
  BinArrayObjEntry   *object_entry = NULL;
  logical             lock = YES;
BEGINSEQ
  ILock();
  
  last_used++;
  
  if ( !(obj_entry = BinSArray::ProvideEntry(entry_index,create)) )
                                                     ERROR
  object_entry = (BinArrayObjEntry *)obj_entry;
  
  if ( !object_entry->get_use_count() )
    RegUnusedEntry(object_entry);

RECOVER
  object_entry = NULL;
ENDSEQ
  if ( lock )
    IUnlock();
  return(object_entry);
}

/******************************************************************************/
/**
\brief  RegUnusedEntry


\param  object_entry
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegUnusedEntry"

void BinArray :: RegUnusedEntry (BinArrayObjEntry *object_entry )
{

  ILock();
  if ( !object_entry->get_use_count() )
  {
    if ( !object_entry->get_free_entry() && last_free_entry != object_entry && first_free_entry != object_entry)
    {
      unused_entries++;
      object_entry->SetPrevious(last_free_entry);
      last_free_entry = object_entry;
    }
  }
  IUnlock();


}

/******************************************************************************/
/**
\brief  RelObjEntry - Release object entry
        The  function is  called, when  an object  entry is going to be released
        because  of an error. An error occurs,  when a closing thread is calling
        the  ReleaseLockedEntries()  function  for  releasing entries, which are
        still  locked  in  the  array.  The  function  can  be overloaded by the
        derived array implementation.


\param  obj_entry
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RelObjEntry"

void BinArray :: RelObjEntry (BinSArrayObjEntry *obj_entry )
{



}

/******************************************************************************/
/**
\brief  ReleaseEntry

\return object_entry

\param  entry_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseEntry"

BinArrayObjEntry *BinArray :: ReleaseEntry (uint64 entry_index )
{
  BinArrayObjEntry       *object_entry;

  ILock();
  
  last_used++;
  
  if ( object_entry = ProvideEntryIntern(entry_index,NO) )
    if ( !WaitForEntry(object_entry) ) // vielleicht müssen wir noch den use_count mit abfragen (!=0) 5.2.2003
      if ( object_entry->Release(last_used) )
        RegUnusedEntry(object_entry);
  
  IUnlock();

  return(object_entry);
}

/******************************************************************************/
/**
\brief  ReleaseLockedEntries - Release locked entries
        The  function  can  be  used  to  release  entries  locked ba the thread
        passed.  When  no  thread  is  passed, the function releases all entries
        owned  by the current  thread. The function  returns true (YES), when at
        least one locked entry was found and NO otherwise.
        The  function  can  be  called  to  release entries, which are locked by
        mistake, when the owning theread is going to be closed.

\return term - Success

\param  threadid
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseLockedEntries"

logical BinArray :: ReleaseLockedEntries (thread_t threadid )
{
  BinArrayObjEntry       *object_entry;
  logical                 term = NO;
  if ( !threadid )
    threadid = ThreadEntry::GetThreadID();

  GoTop();
  while ( object_entry = GetNext() )
    if ( object_entry->stscwpt() )
      term = object_entry->ReleaseLock(threadid);
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveEntry

\return object_entry

\param  entry_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveEntry"

BinArrayObjEntry *BinArray :: RemoveEntry (uint64 entry_index )
{
  BinArrayObjEntry  *obj_entry;

  if ( obj_entry = (BinArrayObjEntry *)BinSArray::RemoveEntry(entry_index) )
  {
    obj_entry->ResetUseCount();
    obj_entry->SetPrevious(NULL);
  }

  return (obj_entry);
}

/******************************************************************************/
/**
\brief  Reorganize

\return term - Success

\param  start_num
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reorganize"

logical BinArray :: Reorganize (uint32 start_num )
{
  BinArrayObjEntry       *object_entry;
  BinArrayObjEntry       *prev_entry;
  uint32                  lastnum;
  logical                 term = NO;
BEGINSEQ
  if ( auto_reorg && (unused_entries < (obj_entry_pool.GetEntryCount() >> 4)) )
                                                     ERROR
  ILock();
  
  if ( start_num )
    lastnum = start_num;
  else
  {
    lastnum = last_reorg;
    if ( lastnum < last_used )
      lastnum += (last_used-lastnum)/2;
    else
      lastnum = 0;
  }
  last_reorg = lastnum;
  unused_entries = 0;
  
  prev_entry = last_free_entry;
  last_free_entry = NULL;
  first_free_entry = NULL;
  
  while ( object_entry = prev_entry )
  {
    prev_entry = object_entry->get_free_entry();
    object_entry->SetPrevious(NULL);
    switch ( object_entry->IsCandidate(lastnum) )
    {
      case 0  : break;
      case 1  : RemoveEntry(object_entry->get_object_id());
                break;
      default : RegUnusedEntry(object_entry);
    }
  }
  
  IUnlock();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReserveEntry

\return object_entry

\param  entry_index - 
\param  lock
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveEntry"

BinArrayObjEntry *BinArray :: ReserveEntry (uint64 entry_index, logical lock )
{
  BinArrayObjEntry       *object_entry;
BEGINSEQ
  if ( lock )
    ILock();
  if ( object_entry = ProvideEntryIntern(entry_index,YES) )
  {
    if ( WaitForEntry(object_entry) )                ERROR
      
    object_entry->Reserve();
    if ( last_free_entry == object_entry )
    {
      last_free_entry = object_entry->get_free_entry();
      object_entry->SetPrevious(NULL);
      unused_entries--;
    }
  }

RECOVER
  object_entry = NULL;
ENDSEQ
  if ( lock )
    IUnlock();
  return(object_entry);
}

/******************************************************************************/
/**
\brief  StoreObjEntry


\param  array - 
\param  obj_entry
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreObjEntry"

void BinArray :: StoreObjEntry (BinArray *array, BinSArrayObjEntry *obj_entry )
{
  ((BinArrayObjEntry *)obj_entry)->stsrmod();
}

/******************************************************************************/
/**
\brief  Unlock

\return term - Success

\param  entry_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical BinArray :: Unlock (uint64 entry_index )
{
  BinArrayObjEntry       *object_entry;
  logical                 term = NO;
  if ( object_entry = ProvideEntry(entry_index,NO) )
    term = object_entry->Unlock();

  return(term);
}

/******************************************************************************/
/**
\brief  UnlockInternal

\return term - Success

\param  entry_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockInternal"

logical BinArray :: UnlockInternal (uint64 entry_index )
{
  BinArrayObjEntry       *object_entry;
  logical                 term = NO;
  if ( object_entry = ProvideEntry(entry_index,NO) )
    term = object_entry->UnlockInternal();

  return(term);
}

/******************************************************************************/
/**
\brief  UpdateEntry


\param  entry_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateEntry"

void BinArray :: UpdateEntry (uint64 entry_index )
{
  BinArrayObjEntry       *object_entry;
BEGINSEQ
  ILock();
  
  if ( !(object_entry = ProvideEntryIntern(entry_index,YES)) )
                                                     SOSERR(95)
  if ( WaitForEntry(object_entry) )                  ERROR
  
  if ( !object_entry->stscmod() )
  {
    object_entry->stssmod();
    updated_entries.AddTail(object_entry);
  }
  

RECOVER
ENDSEQ
  IUnlock();

}

/******************************************************************************/
/**
\brief  WaitForEntry

\return term - Success

\param  object_entry
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WaitForEntry"

logical BinArray :: WaitForEntry (BinArrayObjEntry *object_entry )
{
  logical                 term = NO;
BEGINSEQ
//Die Funktion darf nur in gelockten Listen aufgerufen werden!!
  
  object_entry->stssres();
  IUnlock();

  if ( object_entry->get_use_count() )
    if ( object_entry->Wait(200) )                   SOSERR(6)
RECOVER
  term = YES;
ENDSEQ
  ILock();
  object_entry->stsrres();
  return(term);
}

/******************************************************************************/
/**
\brief  ~BinArray


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~BinArray"

     BinArray :: ~BinArray ( )
{

  Clear();
}


