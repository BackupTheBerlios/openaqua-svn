/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    ThreadCall

\brief    


\date     $Date: 2006/03/12 19:22:00,15 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ThreadCall"

#include  <pdefault.h>
#include  <cactp.h>
#include  <cfctp.h>
#include  <fileacc.h>
#include  <sThreadEntry.hpp>
#include  <sThreadLink.hpp>
#include  <sflnk.hpp>

#include  <iThreadCall.h>

/******************************************************************************/
/**
\brief  ExecuteThread

\return

\param  flnkinst -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteThread"

thrdfnctype __cdecl ExecuteThread (void *flnkinst )
{
  flnk    local_link(*(flnk *)flnkinst);
#ifdef __unix__
  sigset_t       setofsigs;
#endif
#ifdef __unix__
  sigemptyset(&setofsigs);
  sigaddset(&setofsigs,SIGTERM);
  sigaddset(&setofsigs,SIGHUP);
  pthread_sigmask(SIG_BLOCK,&setofsigs,NULL);
#endif
  
  ThreadEntry::CreateEntry();
  local_link.ActionCall();
  ThreadEntry::DeleteEntry();


}

/******************************************************************************/
/**
\brief  ExecuteThreadS

\return

\param  flnkinst -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteThreadS"

thrdfnctype __cdecl ExecuteThreadS (void *flnkinst )
{
  flnk    local_link(*(flnk *)flnkinst);
#ifdef __unix__
  sigset_t       setofsigs;
#endif
#ifdef __unix__
  sigemptyset(&setofsigs);
  sigaddset(&setofsigs,SIGTERM);
  sigaddset(&setofsigs,SIGHUP);
  pthread_sigmask(SIG_BLOCK,&setofsigs,NULL);
#endif
  
  local_link.ActionCall();


}

/******************************************************************************/
/**
\brief  ExecuteThreadT

\return

\param  threadlnk_inst -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteThreadT"

thrdfnctype __cdecl ExecuteThreadT (void *threadlnk_inst )
{
  ThreadLink    local_link(*(ThreadLink *)threadlnk_inst);
  ProcessInfo  *proc_info = NULL;
  logical       locked;
#ifdef __unix__
  sigset_t       setofsigs;
#endif
#ifdef __unix__
  sigemptyset(&setofsigs);
  sigaddset(&setofsigs,SIGTERM);
  sigaddset(&setofsigs,SIGHUP);
  pthread_sigmask(SIG_BLOCK,&setofsigs,NULL);
#endif
  
  ThreadEntry::CreateEntry();
  proc_info = ThreadEntry::GetCurProcInfo();
  proc_info->SetParentInfo(local_link.get_parent_info());
  
  ((ThreadLink *)threadlnk_inst)->Start();
  local_link.ActionCall();
  if ( local_link.get_wait() )
    ((ThreadLink *)threadlnk_inst)->Terminate();
    
  ThreadEntry::DeleteEntry();


}

