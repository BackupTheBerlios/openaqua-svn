/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    ThreadLink

\brief    


\date     $Date: 2006/03/12 19:22:01,48 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ThreadLink"

#include  <pdefault.h>
#include  <cactp.h>
#include  <cfctp.h>
#include  <ctfctp.h>
#include  <fileacc.h>
#include  <iThreadCall.h>
#include  <sThreadEntry.hpp>
#include  <stim.hpp>
#include  <svcls.hpp>
#include  <sThreadLink.hpp>


/******************************************************************************/
/**
\brief  Start - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Start"

void ThreadLink :: Start ( )
{

  started.Set();



}

/******************************************************************************/
/**
\brief  Terminate


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Terminate"

void ThreadLink :: Terminate ( )
{

  terminated.Set();

}

/******************************************************************************/
/**
\brief  ThreadCall

\return thread_id -

\param  wait_for_termination
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ThreadCall"

thread_t ThreadLink :: ThreadCall (logical wait_for_termination )
{
thread_t thread_id;
BEGINSEQ
  if ( !flnkinst )                                   SOSERR(99)
  if ( wait_for_termination )
    wait = YES;

#ifdef __unix__
  pthread_attr_t attr;
  pthread_attr_init (&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  switch ( pthread_create(&thread_id, &attr, ExecuteThreadT, this) )
  {
    case 0      : pthread_attr_destroy(&attr);
                  break;
    case EAGAIN : pthread_attr_destroy(&attr);
                  SOSERR(900+EAGAIN)
    default     : pthread_attr_destroy(&attr);
                  SOSERR(99);
  }
#else
  if ( (thread_id = _beginthread(ExecuteThreadT,8000,this)) == -1)
    switch ( errno )
    {
      case  EAGAIN : ERROR 
      default      : SOSERR(99);
    }
#endif
  started.WaitForSet(AUTO);
  
  if ( wait_for_termination )
    terminated.WaitForSet(AUTO);

RECOVER

ENDSEQ
  return(thread_id);

}

/******************************************************************************/
/**
\brief  ThreadLink

-------------------------------------------------------------------------------
\brief FLNK_


\param  vclsptr - Virtual class pointer
\param  funcptr - Function pointer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ThreadLink"

                        ThreadLink :: ThreadLink (vcls *vclsptr, FCTP funcptr )
                     : flnk (vclsptr,funcptr),
  started(),
  terminated(),
  parent_info(NULL),
  wait(NO)
{

  parent_info = ThreadEntry::GetCurProcInfo();

}

/******************************************************************************/
/**
\brief FLNK_A


\param  vclsptr - Virtual class pointer
\param  actptri - Action pointer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ThreadLink"

                        ThreadLink :: ThreadLink (vcls *vclsptr, ACTP actptri )
                     : flnk (vclsptr,actptri),
  started(),
  terminated(),
  parent_info(NULL),
  wait(NO)
{

  parent_info = ThreadEntry::GetCurProcInfo();

}

/******************************************************************************/
/**
\brief FLNK_C


\param  threadlnk_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ThreadLink"

                        ThreadLink :: ThreadLink (ThreadLink &threadlnk_ref )
                     : flnk (threadlnk_ref),
  started(),
  terminated(),
  parent_info(threadlnk_ref.get_parent_info()),
  wait(threadlnk_ref.get_wait())
{



}

/******************************************************************************/
/**
\brief FLNK_DUM


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ThreadLink"

                        ThreadLink :: ThreadLink ( )
                     : flnk (),
  started(),
  terminated(),
  parent_info(NULL),
  wait(NO)
{



}

/******************************************************************************/
/**
\brief  ~ThreadLink


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ThreadLink"

                        ThreadLink :: ~ThreadLink ( )
{



}


