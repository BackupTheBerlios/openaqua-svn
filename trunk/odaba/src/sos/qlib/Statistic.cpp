/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    Statistic

\brief    


\date     $Date: 2006/08/27 18:39:08,57 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "Statistic"

#include  <pdefault.h>
#include  <sStatistic.hpp>


/******************************************************************************/
/**
\brief  GetCalls - 



\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCalls"

char *Statistic :: GetCalls ( )
{
  static char      string[256];
  memcpy(string,"ZZZZZZZZZ9",10);
  gvtxltp(string,calls,10);

  return(string);
}

/******************************************************************************/
/**
\brief  GetMaxTime - 



\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMaxTime"

char *Statistic :: GetMaxTime ( )
{

  return( strcat(GetTime(max_time,1000)," ms") );

}

/******************************************************************************/
/**
\brief  GetMinTime - 



\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMinTime"

char *Statistic :: GetMinTime ( )
{

  return( strcat(GetTime(min_time,1000)," ms") );

}

/******************************************************************************/
/**
\brief  GetOutput - 



\return line - 

\param  objecttype - 
\param  head_line - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOutput"

char *Statistic :: GetOutput (char *objecttype, logical head_line )
{
  struct       statline {
                          char   space1[2];
                          char   object[15]; 
                          char   space2[2];
                          char   calls[10]; 
                          char   space3[2];
                          char   tot_time[11]; 
                          char   space4[2];
                          char   min_time[11]; 
                          char   space5[2];
                          char   max_time[11]; 
                          char   nl;
                          char   term;
                        } sl;
  static      char        line[sizeof(sl)*3+1];
  int32                   i = 0;
  memset(&sl,' ',sizeof(sl));
  memset(line,0,sizeof(line));
  
  sl.nl = '\n';
  sl.term = 0;
  if ( head_line )
  {
    gvtxstb(sl.object,"Object",sizeof(sl.object)); 
    gvtxstb(sl.calls,"     Calls",sizeof(sl.calls)); 
    gvtxstb(sl.tot_time," Total Time",sizeof(sl.tot_time)); 
    gvtxstb(sl.min_time,"  min. Time",sizeof(sl.min_time)); 
    gvtxstb(sl.max_time,"  max. Time",sizeof(sl.max_time)); 
    memcpy(line,(char *)&sl,sizeof(sl));
    memset(&sl,'-',sizeof(sl)-2);
    memcpy(line+sizeof(sl),(char *)&sl,sizeof(sl));
    memset(&sl,' ',sizeof(sl)-2);
    i = 2;
  }
  gvtxstb(sl.object,objecttype,sizeof(sl.object)); 
  gvtxstb(sl.calls,GetCalls(),sizeof(sl.calls)); 
  gvtxstb(sl.tot_time,GetTotalTime(),sizeof(sl.tot_time)); 
  gvtxstb(sl.min_time,GetMinTime(),sizeof(sl.min_time)); 
  gvtxstb(sl.max_time,GetMaxTime(),sizeof(sl.max_time)); 
  memcpy(line+i*sizeof(sl),(char *)&sl,sizeof(sl));

  return(line);
}

/******************************************************************************/
/**
\brief  GetTime - 



\return string - String value

\param  u_time - 
\param  factor - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTime"

char *Statistic :: GetTime (int64 u_time, int32 factor )
{
  uint64                  time;
  static char             string[256];
  time = (u_time*1000*factor)/perf_freq;

  strcpy(string,"ZZZZZZ9,999");
  gvtxltp(string,(uint32)time,11);

  return(string);
}

/******************************************************************************/
/**
\brief  GetTimeLong - 



\return time - 

\param  u_time - 
\param  factor - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTimeLong"

uint32 Statistic :: GetTimeLong (int64 u_time, int32 factor )
{

  return((uint32)((u_time*1000*factor)/perf_freq));


}

/******************************************************************************/
/**
\brief  GetTotalTime - 



\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTotalTime"

char *Statistic :: GetTotalTime ( )
{

  return( strcat(GetTime(total_time,1)," sec") );

}

/******************************************************************************/
/**
\brief  Initialize - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void Statistic :: Initialize ( )
{

  calls = 0;
  start_time = 0;
  total_time = 0;
  max_time   = 0;
  min_time   = LONGMAX;

}

/******************************************************************************/
/**
\brief  IsStarted - 



\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsStarted"

logical Statistic :: IsStarted ( )
{

  return(use_count ? YES : NO);

}

/******************************************************************************/
/**
\brief  Print - 



\return term - Success

\param  objecttype - 
\param  head_line - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Print"

logical Statistic :: Print (char *objecttype, logical head_line )
{
  char                   *line = GetOutput(objecttype,head_line);
  logical                 term = NO;
  if ( head_line )
  {
    SystemOutput("\n\n",NO,NO);
    SystemOutput(line,NO,NO);
    line = line + strlen(line)+1;
    SystemOutput(line,NO,NO);
    line = line + strlen(line)+1;
  }
  SystemOutput(line,NO,YES);

  return(term);
}

/******************************************************************************/
/**
\brief  Start - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Start"

void Statistic :: Start ( )
{

BEGINSEQ
  calls++;
  exectim = 0;
  if ( use_count )                                   LEAVESEQ
  
#ifdef __unix__
  start_time = clock();
#else
  QueryPerformanceCounter( (LARGE_INTEGER*) &start_time );
#endif

ENDSEQ
  use_count++;
}

/******************************************************************************/
/**
\brief  Statistic - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Statistic"

     Statistic :: Statistic ( )
                     : calls(0),
  start_time(0),
  total_time(0),
  perf_freq(1000000),
  max_time(0),
  min_time(LONGMAX),
  use_count(0)
{

#ifndef __unix__
   QueryPerformanceFrequency( (LARGE_INTEGER*)&perf_freq );
#endif


}

/******************************************************************************/
/**
\brief  Stop - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Stop"

void Statistic :: Stop ( )
{
  int64       exectim = 0;

BEGINSEQ
  if ( !use_count )                                  LEAVESEQ
  if ( --use_count )                                 LEAVESEQ
#ifdef __unix__
  exectim = clock();
#else
  QueryPerformanceCounter( (LARGE_INTEGER*) &exectim );
#endif

  exectim -= start_time;
  
  total_time += exectim;
  if ( exectim > max_time )
    max_time = exectim;
  if ( exectim < min_time )
    min_time = exectim;
  
  start_time = 0;

ENDSEQ

}

/******************************************************************************/
/**
\brief  TraceMessage - 




\param  objecttype - 
\param  head_line - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TraceMessage"

void Statistic :: TraceMessage (char *objecttype, logical head_line )
{
  char               *headline;
  char               *underline;
  char               *line;
  line = GetOutput(objecttype,head_line);

  if ( head_line )
  {
    headline = line;
    underline = strchr(line,'\n');
    *underline = 0;
    underline += 2;
    line = strchr(underline,'\n');
    *line = 0;
    line += 2;
    SOSError().TraceMessage(headline);
    SOSError().TraceMessage(underline);
  }
  *strchr(line,'\n') = 0;
  SOSError().TraceMessage(line);


}

/******************************************************************************/
/**
\brief  operator+= - 



\return ref_statistic - 

\param  ref_statistic - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+="

Statistic &Statistic :: operator+= (Statistic &ref_statistic )
{

  exectim = ref_statistic.exectim;

  total_time += exectim;
  if ( exectim > max_time )
    max_time = exectim;
  if ( exectim < min_time )
    min_time = exectim;

  return(*this);
}

/******************************************************************************/
/**
\brief  ~Statistic - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~Statistic"

     Statistic :: ~Statistic ( )
{



}


