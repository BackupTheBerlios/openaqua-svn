/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    RessourceLock

\brief    


\date     $Date: 2006/03/12 19:21:57,89 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "RessourceLock"

#include  <pdefault.h>
#include  <creslck.h>
#ifndef   DLL_RessourceLock_HPP
#define   DLL_RessourceLock_HPP
#include  <sRessourceLock.hpp>
#include  <sDLL.h>
#endif
#include  <sCRITICAL_SECTION.hpp>
#include  <sThreadEntry.hpp>
#include  <sRessourceLock.hpp>


/******************************************************************************/
/**
\brief  ActivateLockList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateLockList"

void RessourceLock :: ActivateLockList ( )
{

  thread_locks = NULL;

}

/******************************************************************************/
/**
\brief  ActiveLockList

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActiveLockList"

logical RessourceLock :: ActiveLockList ( )
{

  return ( thread_locks != (DLL(RessourceLock) *)(-1) );

}

/******************************************************************************/
/**
\brief  DeactivateLockList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeactivateLockList"

void RessourceLock :: DeactivateLockList ( )
{

  thread_locks = (DLL(RessourceLock) *)(-1);

}

/******************************************************************************/
/**
\brief  ILock

\return term - Success

\param  wait -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ILock"

logical RessourceLock :: ILock (logical wait )
{
  extern int              lck;
  logical                 term = NO;

BEGINSEQ
  if ( !this )                                       ERROR
#ifdef __unix__
  if ( pthread_equal(lock_object.locker_id, pthread_self()) )
    lock_object.lockcount++;
  else
  {
    pthread_mutex_lock(&lock_object.mutex);
    lock_object.locker_id = pthread_self();
    lock_object.lockcount++;
  }
#else
  EnterCriticalSection(&lock_object);
#endif
  lck++;
  if ( ActiveLockList() && 
       (thread_locks = ThreadEntry::GetLockList()) )
    thread_locks->AddTail(this);
RECOVER

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IUnlock

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IUnlock"

logical RessourceLock :: IUnlock ( )
{
  extern int              lck;
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( thread_locks && ActiveLockList() )
    thread_locks->Remove(this);

#ifdef __unix__
  if ( pthread_equal(lock_object.locker_id, pthread_self()) )
  {  
    if ( lock_object.lockcount )
      lock_object.lockcount--;
    if ( !lock_object.lockcount )
    {  
      lock_object.locker_id=nullthread;
      pthread_mutex_unlock(&lock_object.mutex);
    }
  }
#else
  if ( lock_object.RecursionCount == 0 )
    ERROR
    
  LeaveCriticalSection(&lock_object);
  
#endif
  lck--;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void RessourceLock :: Initialize ( )
{

BEGINSEQ
  if ( !this )                                       ERROR
#ifdef __unix__
  pthread_once(&nullthread_control, nullthread_create);
  pthread_mutex_init(&lock_object.mutex, NULL);
  lock_object.lockcount=0;
  lock_object.locker_id=nullthread;
#else
  InitializeCriticalSection(&lock_object);
#endif
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  IsLocked - 


\return cond - Return value

\param  wait -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsLocked"

logical RessourceLock :: IsLocked (logical wait )
{
  extern int              lck;
  logical                 cond = YES;

BEGINSEQ
  if ( !this )                                       ERROR
#ifdef __unix__
  if ( lock_object.lockcount <= 0 )                  ERROR
#else
  if ( lock_object.LockCount + lock_object.RecursionCount <= 0 )                  
                                                     ERROR
#endif


RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  RessourceLock


\param  activate_llist
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RessourceLock"

                        RessourceLock :: RessourceLock (logical activate_llist )
{

  Initialize();
  if ( activate_llist )
    ActivateLockList();
  else
    DeactivateLockList();

}

/******************************************************************************/
/**
\brief  Uninitialize


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Uninitialize"

void RessourceLock :: Uninitialize ( )
{

BEGINSEQ
  if ( !this )                                       ERROR
#ifdef __unix__
  pthread_mutex_destroy(&lock_object.mutex);
#else
  DeleteCriticalSection(&lock_object);
#endif
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~RessourceLock


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~RessourceLock"

                        RessourceLock :: ~RessourceLock ( )
{

  Uninitialize();

}


