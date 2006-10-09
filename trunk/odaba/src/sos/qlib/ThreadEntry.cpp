/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    ThreadEntry

\brief    


\date     $Date: 2006/03/12 19:22:00,34 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ThreadEntry"

#include  <pdefault.h>
#include  <exthrde.h>
#include  <fileacc.h>
#include  <threini.h>
#ifndef   GSRT_ThreadEntry_HPP
#define   GSRT_ThreadEntry_HPP
#include  <sThreadEntry.hpp>
#include  <sGSRT.h>
#endif
#include  <sProcessInfo.hpp>
#include  <sProcessVariables.hpp>
#include  <sRessourceLock.hpp>
#include  <sThreadEntry.hpp>
#include  <sThreadEntry.hpp>


/******************************************************************************/
/**
\brief  CreateCurProcInfo

\return procinfo -

\param  proc_variables - Process variables
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCurProcInfo"

ProcessInfo *__cdecl ThreadEntry :: CreateCurProcInfo (ProcessVariables *proc_variables )
{
  ThreadEntry     *te_ptr;
  ProcessInfo     *proc_info = NULL;
BEGINSEQ
  if ( !thread_list || !thread_list->IsInitialized() )
                                                     ERROR
  if ( te_ptr = LocateEntry() )
  {
    if ( te_ptr->IsDeleting() )                      ERROR
  }
  else
    CreateEntry();
  
  if ( !(proc_info = GetCurProcInfo()) )
    SetCurProcInfo(proc_info = new ProcessInfo());
    
  if ( proc_variables )
    proc_info->SetProcessVariables(proc_variables);


RECOVER

ENDSEQ
  return(proc_info);
}

/******************************************************************************/
/**
\brief  CreateEntry


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateEntry"

void __cdecl ThreadEntry :: CreateEntry ( )
{
  ThreadEntry    *te_ptr;
  if ( !Lock() )
  {
    if ( !(te_ptr = LocateEntry()) )
    {
      ThreadEntry    thent;
      thread_list->AddEntry(&thent);
      SetCurProcInfo(new ProcessInfo());
    }
    else
      te_ptr->use_count++;
    thread_list->Unlock();
  }

}

/******************************************************************************/
/**
\brief  DeleteEntry - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteEntry"

logical __cdecl ThreadEntry :: DeleteEntry ( )
{
  thread_t             threadid = GetThreadID();
  ThreadEntry         *te_ptr   = NULL;
  ProcessInfo         *proc_info  = NULL;
  DLL(RessourceLock)  *lock_list  = NULL;
  int32                index    = 0;
  logical              term     = NO;
BEGINSEQ
  if ( !Lock() )
  {
    if ( index = thread_list->FindEntry(&threadid) )
    {
      te_ptr = thread_list->GetEntry(index);
      te_ptr->deleting = YES;
      proc_info = te_ptr->reset_process_info();
      lock_list = te_ptr->reset_ilock_list();
      
      Unlock();
      Uninitialize(proc_info,lock_list); // das darf nicht im gelockten Zustand passieren!!
      if ( Lock() )                                  ERROR

      if ( thread_list )
      {
        if ( index = thread_list->FindEntry(&threadid) )
          thread_list->DeleteEntry(index);
        
        if ( thread_list->GetCount() == 0 )
        {
          Unlock();
          delete thread_list;
          thread_list = NULL;
        }
      }
    }
    else
      te_ptr = NULL;
      
    if ( thread_list )
      Unlock();
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetCount - 


\return count -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int16 __cdecl ThreadEntry :: GetCount ( )
{
  short     count = 0;
  if ( !Lock() )
  {
    count = thread_list->GetCount();
    thread_list->Unlock();
  }
  return(count);
}

/******************************************************************************/
/**
\brief  GetCurProcInfo

\return procinfo -

\param  proc_vt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurProcInfo"

ProcessInfo *__cdecl ThreadEntry :: GetCurProcInfo (ProcVariableTypes proc_vt )
{
  ThreadEntry   *thread_ptr = NULL;
  ProcessInfo   *procinfo = NULL;
  if ( !Lock() )
  {
    if ( thread_ptr = LocateEntry() )   
    {          
      if ( !thread_ptr->IsDeleting() )
      {
        procinfo = thread_ptr->get_process_info();
  
        if ( proc_vt > 0 && !procinfo->GetVariableManager(proc_vt) )
          procinfo = NULL;
      }
    }
    Unlock();
  }
  return(procinfo);
}

/******************************************************************************/
/**
\brief  GetLockList

\return ilock_list

\param  proc_vt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLockList"

DLL(RessourceLock) *__cdecl ThreadEntry :: GetLockList (ProcVariableTypes proc_vt )
{
  ThreadEntry        *thread_ptr = NULL;
  DLL(RessourceLock) *ilock_list = NULL;
  if ( !Lock() )
  {
    if ( thread_ptr = LocateEntry() )   
      ilock_list = thread_ptr->get_ilock_list();
    Unlock();
  }
  return(ilock_list);
}

/******************************************************************************/
/**
\brief  GetProcessUseCount

\return use_count -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetProcessUseCount"

int32 __cdecl ThreadEntry :: GetProcessUseCount ( )
{
  thread_t       threadid = GetThreadID();
  ThreadEntry    *te_ptr;
  int32           use_count = 0;
  short          index;
  ThreadEntry   *thread_ptr = NULL;
  logical        term = NO;
  if ( !Lock() )
  {
    if ( index = thread_list->FindEntry(&threadid) )   
    {
      te_ptr = thread_list->GetEntry(index);
      use_count = te_ptr->use_count;
    }
    thread_list->Unlock();
  }

  return(use_count);
}

/******************************************************************************/
/**
\brief  GetThreadID

\return threadid -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetThreadID"

thread_t __cdecl ThreadEntry :: GetThreadID ( )
{

#ifdef __unix__
  return pthread_self();
#else
  return(GetCurrentThreadId());
#endif

}

/******************************************************************************/
/**
\brief  Initialize - Initialize thread list



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void __cdecl ThreadEntry :: Initialize ( )
{

  if ( !thread_list )
  {
    thread_list = new ThreadList();
    thread_list->Initialize();
  }

}

/******************************************************************************/
/**
\brief  IsDeleting

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsDeleting"

logical ThreadEntry :: IsDeleting ( )
{

  return(deleting);

}

/******************************************************************************/
/**
\brief  LocateEntry

\return thread_ptr

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateEntry"

ThreadEntry *__cdecl ThreadEntry :: LocateEntry ( )
{
  thread_t       threadid = GetThreadID();
  ThreadEntry   *thread_ptr = NULL;
  thread_ptr = thread_list->GetEntry(&threadid);

  return(thread_ptr);
}

/******************************************************************************/
/**
\brief  Lock

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical __cdecl ThreadEntry :: Lock ( )
{
  logical                 term = NO;
BEGINSEQ
  Initialize();
  if ( !thread_list )                                ERROR
  if ( thread_list->Lock() )                         ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RegisterLock


\param  res_lock
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegisterLock"

void ThreadEntry :: RegisterLock (RessourceLock *res_lock )
{

  ilock_list->AddTail(res_lock);

}

/******************************************************************************/
/**
\brief  ReleaseLocks


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseLocks"

void __cdecl ThreadEntry :: ReleaseLocks ( )
{
  DLL(RessourceLock) *ilock_list = GetLockList();
  RessourceLock      *res_lock;
  while ( res_lock = ilock_list->RemoveTail() )
    res_lock->IUnlock();


}

/******************************************************************************/
/**
\brief  RemoveEntry

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveEntry"

logical __cdecl ThreadEntry :: RemoveEntry ( )
{
  thread_t       threadid = GetThreadID();
  ThreadEntry    *te_ptr  = NULL;
  short          index;
  ThreadEntry   *thread_ptr = NULL;
  logical        term = NO;
BEGINSEQ
  if ( !thread_list )                                ERROR // Lock legt diese sonst an und es laeuft ein SOSRESET
    
  if ( !Lock() )
  {
    if ( index = thread_list->FindEntry(&threadid) )
    {
      te_ptr = thread_list->GetEntry(index);
      if ( thread_list )
        Unlock();
      if ( --te_ptr->use_count <= 0 )
        DeleteEntry();
    }
    else
      term = YES;
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetCurProcInfo

\return term - Success

\param  procinfo -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCurProcInfo"

logical __cdecl ThreadEntry :: SetCurProcInfo (ProcessInfo *procinfo )
{
  ThreadEntry   *thread_ptr = NULL;
  logical        term = NO;
  if ( !Lock() )
  {
    if ( thread_ptr = LocateEntry() )
      thread_ptr->process_info = procinfo;
    else
      term = YES;
    thread_list->Unlock();
  }
  return(term);
}

/******************************************************************************/
/**
\brief  ThreadEntry


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ThreadEntry"

                        ThreadEntry :: ThreadEntry ( )
                     :   thread_id(GetThreadID()),
  process_info(NULL),
  use_count(1),
  deleting(NO)
{

  ilock_list = new DLL(RessourceLock)();

}

/******************************************************************************/
/**
\brief  Uninitialize - 



\param  proc_info -
\param  locklist
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Uninitialize"

void __cdecl ThreadEntry :: Uninitialize (ProcessInfo *proc_info, DLL(RessourceLock) *locklist )
{
  Error          *error;
  if ( proc_info )
  {
    if ( locklist )
    {
      if ( locklist->GetCount() > 0 )  
        if ( error = (Error *)proc_info->GetProcessVariable(PVN_SOSError) )
        {
          error->SetError(398,OBJ_ID,MOD_ID);
          error->ResetError();
        }
      locklist->Clear();  // oder ReleaseLocks()
      delete locklist;
    }
    if ( !proc_info->get_is_deleting() )
    {  
      proc_info->ResetParentInfo();   
      delete proc_info;
    }
  }


}

/******************************************************************************/
/**
\brief  Unlock

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical __cdecl ThreadEntry :: Unlock ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !thread_list )                                ERROR
  if ( thread_list->Unlock() )                       ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  UnregisterLock


\param  res_lock
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnregisterLock"

void ThreadEntry :: UnregisterLock (RessourceLock *res_lock )
{

  ilock_list->Remove(res_lock);

}

/******************************************************************************/
/**
\brief  reset_ilock_list

\return locklist

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "reset_ilock_list"

DLL(RessourceLock) *ThreadEntry :: reset_ilock_list ( )
{
  DLL(RessourceLock)  *lock_list = ilock_list;
  ilock_list = NULL;
  return(lock_list);
}

/******************************************************************************/
/**
\brief  reset_process_info

\return proc_info -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "reset_process_info"

ProcessInfo *ThreadEntry :: reset_process_info ( )
{
  ProcessInfo  *proc_info = process_info;
  process_info = NULL;
  return(proc_info);
}

/******************************************************************************/
/**
\brief  set_use_count


\param  count -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_use_count"

void ThreadEntry :: set_use_count (int16 count )
{

  use_count = count;

}

/******************************************************************************/
/**
\brief  ~ThreadEntry


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ThreadEntry"

                        ThreadEntry :: ~ThreadEntry ( )
{



}


