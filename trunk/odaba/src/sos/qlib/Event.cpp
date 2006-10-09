/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    Event

\brief    


\date     $Date: 2006/03/12 19:21:41,04 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "Event"

#include  <pdefault.h>
#include  <win32f.h>
#include  <sEvent.hpp>


/******************************************************************************/
/**
\brief  Event

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Event"

                        Event :: Event ( )
                     : event_object()
{

#ifdef __unix__
  pthread_cond_init (&event_object.condition, NULL);
  pthread_mutex_init(&event_object.mutex,     NULL);
  event_object.set = NO;
#else
  event_object= CreateEvent( NULL, TRUE, FALSE, NULL );
#endif

}

/******************************************************************************/
/**
\brief  Reset - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical Event :: Reset ( )
{
  logical                 term = NO;
#ifdef __unix__
  event_object.set = NO;
#else
  ResetEvent( event_object );
#endif
  return(term);
}

/******************************************************************************/
/**
\brief  Set

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Set"

logical Event :: Set ( )
{
  logical                 term = NO;
#ifdef __unix__
  pthread_mutex_lock(&event_object.mutex);
  event_object.set = YES;
  pthread_cond_broadcast(&event_object.condition);
  pthread_mutex_unlock(&event_object.mutex);
#else
  SetEvent( event_object );
#endif
  return(term);
}

/******************************************************************************/
/**
\brief  WaitForSet

\return term - Success

\param  timeout -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WaitForSet"

logical Event :: WaitForSet (int32 timeout )
{
  logical                 term = NO;
  if( timeout == -1 ) timeout= INFINITE;

#ifdef __unix__
  pthread_mutex_lock(&event_object.mutex);
  if ( event_object.set == YES )
    term = YES;
  else
  {
    if (timeout == INFINITE) 
    {
      pthread_cond_wait(&event_object.condition, &event_object.mutex);
      term = YES;
    }
    else 
    {
      struct timeval  now;
      struct timespec abstime;
    
      gettimeofday (&now, NULL);
      abstime.tv_nsec = (timeout % 1000) + now.tv_usec / 1000;
      abstime.tv_sec  = (timeout / 1000) + now.tv_sec;
      if (abstime.tv_nsec > 1000000000) 
      {
        abstime.tv_nsec -= 1000000000;
        abstime.tv_sec  += 1;
      }
      if ( pthread_cond_timedwait(&event_object.condition, &event_object.mutex, &abstime) == ETIMEDOUT ) 
        term = NO;
      else
        term = YES;
    }
    pthread_mutex_unlock(&event_object.mutex);
  }
#else
  return( WaitForSingleObject( event_object, timeout ) == WAIT_OBJECT_0 );
#endif
  return(term);
}

/******************************************************************************/
/**
\brief  ~Event

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~Event"

                        Event :: ~Event ( )
{

#ifdef __unix__
  pthread_cond_destroy (&event_object.condition);
  pthread_mutex_destroy(&event_object.mutex);
#else
  CloseHandle( event_object );
#endif

}


