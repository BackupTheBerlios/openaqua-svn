/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    BinArrayObjEntry

\brief    


\date     $Date: 2006/03/12 19:21:19,20 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "BinArrayObjEntry"

#include  <pdefault.h>
#include  <sBinArray.hpp>
#include  <sBinArrayObjEntry.hpp>
#include  <sThreadEntry.hpp>
#include  <stim.hpp>
#include  <sBinArrayObjEntry.hpp>


/******************************************************************************/
/**
\brief  Initialize - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void BinArrayObjEntry :: Initialize ( )
{

  BinSArrayObjEntry::Initialize();
  
  use_count  = 0;
  last_use   = 0;
  owner      = 0;
  free_entry = NULL;
  *(sts *)this = sts();

}

/******************************************************************************/
/**
\brief  IsCandidate

\return cond - Return value

\param  release_num -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsCandidate"

logical BinArrayObjEntry :: IsCandidate (uint32 release_num )
{

  free_entry = NULL;
  return ( use_count || stscwpt() || stscres()
           ? 0 
           : !release_num || last_use < release_num ? 1 : 2 );

}

/******************************************************************************/
/**
\brief  IsLocked

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsLocked"

logical BinArrayObjEntry :: IsLocked ( )
{

  return ( stscwpt(2) && owner && owner != ThreadEntry::GetThreadID() );


}

/******************************************************************************/
/**
\brief  Lock - 


\return term - Success

\param  array -
\param  wait -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical BinArrayObjEntry :: Lock (BinArray *array, logical wait )
{
  thread_t    cur_thread;
  logical     locked = NO;
  logical     term   = NO;
BEGINSEQ
  if ( stscwpt(2) && wait )
    Wait(100);                 // max. 10 sek.
  
  array->ILock(); 
  locked = YES;
  
  cur_thread = ThreadEntry::GetThreadID();
  if ( stscwpt(2) || (owner && owner != cur_thread) )
                                                     SOSERR(6)
  owner = cur_thread;
  stsawpt(2);
RECOVER
  term = YES;
ENDSEQ
  if ( locked )
    array->IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  LockInternal - 


\return term - Success

\param  array -
\param  wait -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockInternal"

logical BinArrayObjEntry :: LockInternal (BinArray *array, logical wait )
{
  thread_t    cur_thread;
  logical     term   = NO;
  logical     locked = NO;
BEGINSEQ
  if ( stscwpt(1) && wait )
    WaitInternal(100);  // max. 10 sek.
   
  array->ILock();
  locked = YES;
  
  cur_thread = ThreadEntry::GetThreadID();
  if ( stscwpt(1) || (owner && owner != cur_thread) )
                                                     ERROR
  owner = cur_thread;
  stsawpt(1);
RECOVER
  term = YES;
ENDSEQ
  if ( locked )
    array->IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  ReleaseLock - 


\return term - Success

\param  threadid -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseLock"

logical BinArrayObjEntry :: ReleaseLock (thread_t threadid )
{
  logical                 term = NO;
BEGINSEQ
  if ( !threadid || owner != threadid )              LEAVESEQ
  if ( !stscwpt() )                                  LEAVESEQ
    
  stsrwpt();
  owner = 0;  
  if ( use_count > 0 ) 
    use_count--;

  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ResetUseCount - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetUseCount"

void BinArrayObjEntry :: ResetUseCount ( )
{

  use_count = 0;

}

/******************************************************************************/
/**
\brief  Unlock - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical BinArrayObjEntry :: Unlock ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !stscwpt(2) || owner != ThreadEntry::GetThreadID() )  
                                                          ERROR
  stsrwpt(2);
  if ( !stscwpt() )
    owner = 0;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  UnlockInternal

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockInternal"

logical BinArrayObjEntry :: UnlockInternal ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !stscwpt(1) || owner != ThreadEntry::GetThreadID() )  
                                                          ERROR
  stsrwpt(1);
  if ( !stscwpt() )
    owner = 0;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Wait

\return term - Success

\param  timeout -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Wait"

logical BinArrayObjEntry :: Wait (int32 timeout )
{

  if ( !IsLocked() )
    return(NO);
    
  while ( stscwpt(2) && (timeout-=CYCL) > 0 )
    TWAIT(CYCL);

  return(stscwpt(2));

}

/******************************************************************************/
/**
\brief  WaitInternal

\return term - Success

\param  timeout -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WaitInternal"

logical BinArrayObjEntry :: WaitInternal (int32 timeout )
{

  while ( stscwpt(1) && (timeout-=CYCL) > 0 )
    TWAIT(CYCL);
  return(stscwpt());
}


