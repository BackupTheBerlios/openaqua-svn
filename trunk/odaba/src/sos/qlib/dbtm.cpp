/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    dbtm

\brief    


\date     $Date: 2006/06/23 12:47:01,95 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "dbtm"

#include  <dosdt.h>
#include  <pdefault.h>
#include  <cDataFormSpec.h>
#include  <iNetConversion.h>
#include  <sdfs.hpp>
#include  <sdbtm.hpp>


/******************************************************************************/
/**
\brief  Clear - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

void dbtm :: Clear ( )
{

 dbtmtime = AUTO;

}

/******************************************************************************/
/**
\brief  FromPIF - 



\param  convert - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

void dbtm :: FromPIF (logical convert )
{

  dbtmtime = PIFToLong(dbtmtime,convert);

}

/******************************************************************************/
/**
\brief  FromString - 


\return time - 

\param  string - String value
\param  size - 
\param  time_format - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromString"

dbtm dbtm :: FromString (char *string, uint16 size, int32 time_format )
{
  char          wstring[20];
  char         *strptr = wstring;
  int16         hour    = 0;
  int16         minute  = 0;
  int16         second  = 0;
  int16         hundred = 0;
  memset(wstring,0,sizeof(wstring));
  if ( string )
    gvtxbts(wstring,string,MIN(size,sizeof(wstring)-1));

  if ( !*wstring )
    SetTime();
  else
  {
    if ( time_format == DFS_Default )
      time_format = dfs::GetTimeFormat();
    if ( time_format == DFS_HHMMSSHH )
      if ( strptr = strchr(wstring,',') )
      {
        size    = strptr-wstring;
        strptr++;
        hundred = atoi(strptr) * (strlen(strptr) == 1 ? 10 : 1);
      }
  
    switch ( time_format )
    {
      case DFS_HHMMSS     : size = MIN(8,size);
                            wstring[size] = 0;
                            strptr = wstring+size-1;
                            if ( *(--strptr) == ':' || *(--strptr) == ':' || strptr < wstring )
                              strptr++;
                            second    = atoi(strptr);
                            *strptr = 0;
                            if ( *(--strptr) == ':' )
                              *strptr = 0;
                            size = strlen(wstring);
      case DFS_HHMM       : size = MIN(5,size);
                            wstring[size] = 0;
                            strptr = wstring+size-1;
                            if ( *(--strptr) == ':' || *(--strptr) == ':' || strptr < wstring )
                              strptr++;
                            minute    = atoi(strptr);
                            *strptr = 0;
                            if ( *(--strptr) == ':' )
                              *strptr = 0;
  
                            size = MIN(2,size);
                            wstring[size] = 0;
                            hour      = atoi(wstring);
                            break;
      default             : ;
    }
    
    dbtmtime = dbtm(hour,minute,second,hundred).GetLongInt();
  }


  return(*this);
}

/******************************************************************************/
/**
\brief  FromUnix - 


\return term - Success

\param  unixtimestamp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromUnix"

logical dbtm :: FromUnix (int64 unixtimestamp )
{
  logical      term = NO;
  tm          *tm_ptr;
  tm_ptr = localtime((time_t*)&unixtimestamp);
  dbtmtime = dbtm(tm_ptr->tm_hour,tm_ptr->tm_min,tm_ptr->tm_sec,0).GetLongInt();

  return(term);
}

/******************************************************************************/
/**
\brief  GetHSecond - returns Hundreds of a second
        0..99

\return hsecond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHSecond"

int16 dbtm :: GetHSecond ( )
{
  int32 hsecond = 0;
  hsecond =   GetTime() 
            - GetHour()*360000 
            - GetMinute()*6000 
            - GetSecond()*100;

  return(hsecond);
}

/******************************************************************************/
/**
\brief  GetHour - returns Hour
        0-24

\return hours - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHour"

int16 dbtm :: GetHour ( )
{
  int32             hour = 0;
  hour = (GetTime()/360000);

  return(hour);
}

/******************************************************************************/
/**
\brief  GetHourMinSec - 



\param  hours_ptr - 
\param  minutes_ptr - 
\param  seconds_ptr - 
\param  hseconds_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHourMinSec"

void dbtm :: GetHourMinSec (uint16 *hours_ptr, uint16 *minutes_ptr, uint16 *seconds_ptr, uint16 *hseconds_ptr )
{
  int32  maxtime = (int32)24 * 360000;
  int32  hundsec = IsEmpty() ? 0 : dbtmtime >= maxtime ? dbtmtime%maxtime : dbtmtime;
  int32  value;


  hundsec  -= (value = hundsec/360000) * 360000;
  if ( hours_ptr )  
    *hours_ptr  = (ushort)value;

  hundsec  -= (value = hundsec/6000) * 6000;
  if ( minutes_ptr )
    *minutes_ptr = (ushort)value;
    
  hundsec  -= (value = hundsec/100) * 100;
  if ( seconds_ptr )
    *seconds_ptr = (ushort)value;
    
  if ( hseconds_ptr )
    *hseconds_ptr = (ushort)hundsec;


}

/******************************************************************************/
/**
\brief  GetLongInt - returns timestamp
        this is the uncorrected timestamp
        use GetTime instead

\return dbtmtime - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLongInt"

int32 dbtm :: GetLongInt ( )
{


  return(dbtmtime < 0 ? 0 : dbtmtime );
}

/******************************************************************************/
/**
\brief  GetMinute - returns minutes
        0..59

\return minute - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMinute"

int16 dbtm :: GetMinute ( )
{
  int32 minute = 0;
  minute =  GetTime() 
          - GetHour() * 360000;
  minute = (minute / 6000);
  return(minute);
}

/******************************************************************************/
/**
\brief  GetSecond - returns seconds
        0..59

\return second - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSecond"

int16 dbtm :: GetSecond ( )
{
  int32 second = 0;
  second =   GetTime() 
           - GetHour()*360000 
           - GetMinute()*6000;
  second = (second / 100);
  return(second);
}

/******************************************************************************/
/**
\brief  GetTime - returns Timestamp
        long int 0-8640000
        corrects invalid timestamp to that range

\return time - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTime"

int32 dbtm :: GetTime ( )
{
  int32 maxtime = (int32)24 * 360000;

  return(IsEmpty() ? 0 : dbtmtime >= maxtime ? dbtmtime%maxtime : dbtmtime);
}

/******************************************************************************/
/**
\brief  IsEmpty - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical dbtm :: IsEmpty ( )
{

 return ( dbtmtime < 0 ? YES : NO );

}

/******************************************************************************/
/**
\brief  SetTime - 


\return dbtmref - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTime"

dbtm &dbtm :: SetTime ( )
{
#if defined (WIN32) || defined (__unix__)
//  time_t ltime;
  _timeb  ltime;
  tm     *tm_ptr;
#else
  DOS_TIME ctime;
#endif

  dbtmtime = 0;

#if defined (WIN32) || defined (__unix__)
  _ftime(&ltime);
  tm_ptr = localtime(&(ltime.time));
  dbtmtime = dbtm(tm_ptr->tm_hour,tm_ptr->tm_min,tm_ptr->tm_sec,ltime.millitm/10).GetLongInt();
#else
  _dos_gettime(&ctime);
  dbtmtime = dbtm(ctime.hour,ctime.minute,ctime.second,ctime.hsecond).GetLongInt();
#endif
  return(*this);

}

/******************************************************************************/
/**
\brief  ToPIF - 



\param  convert - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToPIF"

void dbtm :: ToPIF (logical convert )
{

  dbtmtime = LongToPIF(dbtmtime,convert);

}

/******************************************************************************/
/**
\brief  ToString - 


\return string - String value

\param  string - String value
\param  size - 
\param  time_format - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToString"

char *dbtm :: ToString (char *string, uint16 size, int32 time_format )
{
  char          wstring[20];
  uint16        hour    = 0;
  uint16        minute  = 0;
  uint16        second  = 0;
  uint16        hundred = 0;
  GetHourMinSec(&hour,&minute,&second,&hundred);

  memset(string,0,size+1);
  
  if ( !IsEmpty() )
  {
    strcpy(wstring,"99:99:99,99");
    gvtxitp(wstring+9,hundred,2);
    gvtxitp(wstring+6,second,2);
    gvtxitp(wstring+3,minute,2);
    gvtxitp(wstring,hour,2);

    if ( time_format == DFS_Default )
      time_format = dfs::GetTimeFormat();
    switch ( time_format )
    {
      case DFS_HHMMSSHH :                                  break;
      case DFS_HHMMSS   : size = MIN(8,size);              break;
      case DFS_HHMM     : size = MIN(5,size);              break;
      default           : ;
    }
    memcpy(string,wstring,size);
  }

  return(string);
}

/******************************************************************************/
/**
\brief  ToUnix - 


\return datval - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToUnix"

int64 dbtm :: ToUnix ( )
{
  tm time;
  int64 stamp = -1;
  memset(&time,NULL,sizeof(tm));
  time.tm_hour = GetHour();
  time.tm_min  = GetMinute();
  time.tm_sec  = GetSecond();
  stamp = (int64)mktime(&time);

  return(stamp);
}

/******************************************************************************/
/**
\brief  dbtm - 


-------------------------------------------------------------------------------
\brief  DBTM_ - 


\param  timval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbtm"

     dbtm :: dbtm (int32 timval )
{

  memcpy(&dbtmtime,&timval,sizeof(dbtm));

}

/******************************************************************************/
/**
\brief  DBTM_S - 


\param  hours - 
\param  minutes - 
\param  seconds - 
\param  hseconds - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbtm"

     dbtm :: dbtm (uint16 hours, uint16 minutes, uint16 seconds, uint16 hseconds )
                     : dbtmtime(AUTO)

{

  if ( hours < 24  &&  minutes < 60  &&  seconds > 60  || hseconds < 100 )
    dbtmtime = (hours   * 360000L) +
               (minutes * 6000L)   +
               (seconds * 100L)    +
               hseconds;


}

/******************************************************************************/
/**
\brief  operator!= - 


\return cond - Return value

\param  dbtime - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!="

logical dbtm :: operator!= (dbtm dbtime )
{

  return ( dbtmtime != dbtime.GetLongInt() );


}

/******************************************************************************/
/**
\brief  operator+ - 


\return dbtime - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  hsec - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+"

dbtm dbtm :: operator+ (int32 hsec )
{

  return ( dbtm(dbtmtime+hsec) );


}

/******************************************************************************/
/**
\brief  i1 - 


\param  dbtime - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+"

dbtm dbtm :: operator+ (dbtm dbtime )
{

  return ( dbtm(dbtmtime+dbtime.GetLongInt()) );


}

/******************************************************************************/
/**
\brief  operator+= - 


\return dbtime - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  hsec - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+="

dbtm dbtm :: operator+= (int32 hsec )
{

  dbtmtime += hsec; 

  return(*this);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  dbtime - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+="

dbtm dbtm :: operator+= (dbtm dbtime )
{

  dbtmtime += dbtime.GetLongInt();

  return(*this);
}

/******************************************************************************/
/**
\brief  operator- - 


\return dbtime - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  hsec - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator-"

dbtm dbtm :: operator- (int32 hsec )
{

  return ( dbtm(dbtmtime-hsec) );






}

/******************************************************************************/
/**
\brief  i1 - 


\param  dbtime - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator-"

dbtm dbtm :: operator- (dbtm dbtime )
{

  return ( dbtm(dbtmtime-dbtime.GetLongInt()) );


}

/******************************************************************************/
/**
\brief  operator-= - 


\return dbtime - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  hsec - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator-="

dbtm dbtm :: operator-= (int32 hsec )
{

  return ( dbtm(dbtmtime+hsec) );

  return(*this);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  dbtime - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator-="

dbtm dbtm :: operator-= (dbtm dbtime )
{

  dbtmtime -= dbtime.GetLongInt();

  return(*this);
}

/******************************************************************************/
/**
\brief  operator< - 


\return cond - Return value

\param  dbtime - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<"

logical dbtm :: operator< (dbtm dbtime )
{

  return ( dbtmtime <  dbtime.GetLongInt() );


}

/******************************************************************************/
/**
\brief  operator<= - 


\return cond - Return value

\param  dbtime - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<="

logical dbtm :: operator<= (dbtm dbtime )
{

  return ( dbtmtime <=  dbtime.GetLongInt() );

}

/******************************************************************************/
/**
\brief  operator= - 


\return dbtime - 

\param  hsec - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

dbtm dbtm :: operator= (int32 hsec )
{

  dbtmtime = hsec;
  return(*this);
}

/******************************************************************************/
/**
\brief  operator== - 


\return cond - Return value

\param  dbtime - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical dbtm :: operator== (dbtm dbtime )
{

  return ( dbtmtime == dbtime.GetLongInt() );


}

/******************************************************************************/
/**
\brief  operator> - 


\return cond - Return value

\param  dbtime - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator>"

logical dbtm :: operator> (dbtm dbtime )
{

  return ( dbtmtime >  dbtime.GetLongInt() );

}

/******************************************************************************/
/**
\brief  operator>= - 


\return cond - Return value

\param  dbtime - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator>="

logical dbtm :: operator>= (dbtm dbtime )
{

  return ( dbtmtime >=  dbtime.GetLongInt() );

}


