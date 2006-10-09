/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    ThreadList

\brief    


\date     $Date: 2006/03/12 19:22:01,85 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ThreadList"

#include  <pdefault.h>
#include  <exthrde.h>
#include  <sRessourceLock.hpp>
#include  <sThreadEntry.hpp>
#include  <sThreadList.hpp>


/******************************************************************************/
/**
\brief  Initialize - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void ThreadList :: Initialize ( )
{
  ThreadEntry    *te_ptr;
  Lock();
  
  srtset(10,sizeof(ThreadEntry),sizeof(thread_t),
         offsetof(ThreadEntry,thread_id)+1,'I',YES);

  if ( srtcnt() > 0 ) // srtini legt einen thread-entry an, was nicht sein sollte
  {
    te_ptr = GetEntry(1);
    te_ptr->set_use_count(0);
  }
  
  Unlock();

}

/******************************************************************************/
/**
\brief  IsInitialized

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsInitialized"

logical ThreadList :: IsInitialized ( )
{

  return(this && srtenty ? YES : NO);

}

/******************************************************************************/
/**
\brief  IsLocked - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsLocked"

logical ThreadList :: IsLocked ( )
{

  return(locked);

}

/******************************************************************************/
/**
\brief  Lock - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical ThreadList :: Lock ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( res_lock->ILock(YES) )                        ERROR
  locked++;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void __cdecl ThreadList :: Reset ( )
{
  ThreadEntry    *te_ptr  = NULL;
  if ( thread_list )
  {
    while ( te_ptr = thread_list->GetEntry(1) )
    {
      ThreadEntry::Uninitialize(te_ptr->reset_process_info(),te_ptr->reset_ilock_list());
      thread_list->DeleteEntry(1);
    }
    delete thread_list;
    thread_list = NULL;
  }

}

/******************************************************************************/
/**
\brief  ThreadList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ThreadList"

                        ThreadList :: ThreadList ( )
                     : GSRT(ThreadEntry)(),
  res_lock(new RessourceLock(NO)),
  locked(0)
{



}

/******************************************************************************/
/**
\brief  Unlock - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical ThreadList :: Unlock ( )
{
  logical                 term = NO;
  res_lock->IUnlock();
  locked--;

  return(term);
}

/******************************************************************************/
/**
\brief  ~ThreadList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ThreadList"

                        ThreadList :: ~ThreadList ( )
{

  delete res_lock;
  res_lock = NULL;

}


