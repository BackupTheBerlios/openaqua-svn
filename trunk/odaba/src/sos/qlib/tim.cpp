/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    tim

\brief    


\date     $Date: 2006/03/12 19:22:50,93 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "tim"

#include  <dosdt.h>
#include  <pdefault.h>
#include  <win32f.h>
#include  <stim.hpp>


/******************************************************************************/
/**
\brief  WaitMilliseconds


\param  short_time
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WaitMilliseconds"

void __cdecl tim :: WaitMilliseconds (uint32 short_time )
{

#ifdef __unix__
  struct timespec sleeptime={(short_time/1000), (short_time%1000)*100000000};
  nanosleep(&sleeptime, NULL);
#else
  Sleep(short_time); // 1/1000 seconds
#endif



}

/******************************************************************************/
/**
\brief  timestp


\param  sleeping_time -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "timestp"

void __cdecl tim :: timestp (uint16 sleeping_time )
{
  logical                 term = NO;
#ifdef __unix__
  struct timespec sleeptime={(sleeping_time/10), (sleeping_time%10)*100000000};
  nanosleep(&sleeptime, NULL);
#else
  Sleep(sleeping_time*100); // 1/1000 seconds
#endif



}


