/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    dttm

\brief    


\date     $Date: 2006/06/12 12:49:06,78 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "dttm"

#include  <pdefault.h>
#include  <sdttm.hpp>


/******************************************************************************/
/**
\brief  Clear - 


\return datetime - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

dttm &dttm :: Clear ( )
{

  date = dbdt();
  time.Clear();
  return(*this);
}

/******************************************************************************/
/**
\brief  FromPIF - 



\param  convert - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

void dttm :: FromPIF (logical convert )
{

  date.FromPIF(convert);
  time.FromPIF(convert);

}

/******************************************************************************/
/**
\brief  FromString - 


\return time - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromString"

dbtm dttm :: FromString ( )
{
  logical                 term = NO;

  return(term);
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

logical dttm :: FromUnix (int64 unixtimestamp )
{
  logical      term = NO;

  date.FromUnix(unixtimestamp);
  time.FromUnix(unixtimestamp);

  return(term);
}

/******************************************************************************/
/**
\brief  GetDate - 


\return date - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDate"

dbdt &dttm :: GetDate ( )
{

  return(date);


}

/******************************************************************************/
/**
\brief  GetTime - 


\return time - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTime"

dbtm &dttm :: GetTime ( )
{

  return(time);


}

/******************************************************************************/
/**
\brief  IsEmpty - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical dttm :: IsEmpty ( )
{

  return ( date.IsEmpty() && time.IsEmpty() );


}

/******************************************************************************/
/**
\brief  Normalize - 


\return dbdatetime - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Normalize"

dttm &dttm :: Normalize ( )
{

   return( *this += 0 );


}

/******************************************************************************/
/**
\brief  SetCurDate - 


\return dbdatetime - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCurDate"

dttm &dttm :: SetCurDate ( )
{

  date.SetDate(); 

  return (*this);
}

/******************************************************************************/
/**
\brief  SetCurTime - 


\return dbdatetime - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCurTime"

dttm &dttm :: SetCurTime ( )
{

  time.SetTime(); 

  return (*this);
}

/******************************************************************************/
/**
\brief  SetCurrent - 


\return dbdatetime - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCurrent"

dttm &dttm :: SetCurrent ( )
{

  date.SetDate();
  time.SetTime(); 

  return (*this);
}

/******************************************************************************/
/**
\brief  SetDate - 


\return dbdatetime - 

\param  dbdate - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDate"

dttm &dttm :: SetDate (dbdt dbdate )
{

  date = dbdate; 

  return (*this);
}

/******************************************************************************/
/**
\brief  SetTime - 


\return dbdatetime - 

\param  dbtime - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTime"

dttm &dttm :: SetTime (dbtm dbtime )
{

  time = dbtime;
  return (*this);
}

/******************************************************************************/
/**
\brief  ToPIF - 



\param  convert - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToPIF"

void dttm :: ToPIF (logical convert )
{

  date.ToPIF(convert);
  time.ToPIF(convert);

}

/******************************************************************************/
/**
\brief  ToUnix - 


\return datval - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToUnix"

int64 dttm :: ToUnix ( )
{
  int64      stamp = -1;
  int64     tstamp = -1;
  int64     dstamp = -1;

  tstamp = time.ToUnix(); // ~about 1970+time
  stamp  = date.ToUnix(); // only the date
  stamp+=tstamp;

  return(stamp);
}

/******************************************************************************/
/**
\brief  dttm - 


-------------------------------------------------------------------------------
\brief  DTTM_ - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dttm"

     dttm :: dttm ( )
                     : date(), time()

{



}

/******************************************************************************/
/**
\brief  DTTM_I - 


\param  dbdate - 
\param  dbtime - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dttm"

     dttm :: dttm (dbdt dbdate, dbtm dbtime )
                     : date(dbdate.GetLongInt()), 
time(dbtime.GetLongInt())

{

  Normalize();


}

/******************************************************************************/
/**
\brief  operator!= - 


\return cond - Return value

\param  dbdatetime - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!="

logical dttm :: operator!= (dttm dbdatetime )
{

  return ( date != dbdatetime.GetDate() ||
           time != dbdatetime.GetTime()   );

}

/******************************************************************************/
/**
\brief  operator+ - 


\return dbdatetime - 

\param  duration - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+"

dttm dttm :: operator+ (uint32 duration )
{
  int32   sec  = time.GetLongInt()/100 + duration;
  int32   sday = (int32)24*3600;
  dttm    datetime;
  return(dttm(dbdt(date+sec/sday),dbtm((sec%sday)*100)));


}

/******************************************************************************/
/**
\brief  operator+= - 


\return dbdatetime - 

\param  duration - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+="

dttm &dttm :: operator+= (uint32 duration )
{
  int32 sec  = time.GetLongInt()/100 + duration;
  int32 sday = (int32)24*3600;

  date += sec/sday;
  time  = (sec%sday)*100;

  return(*this);
}

/******************************************************************************/
/**
\brief  operator- - 


\return diff - 

\param  dbdatetime - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator-"

uint32 dttm :: operator- (dttm dbdatetime )
{
  uint32    duration = 0;
  int32     dday;
  int32     dtim;
BEGINSEQ
  Normalize();
  dbdatetime.Normalize();
  
  dday = date.GetLongInt() - dbdatetime.GetDate().GetLongInt();
  dtim = time.GetLongInt() - dbdatetime.GetTime().GetLongInt();

  if ( dday < 0 || (dday == 0 && dtim < 0) )         ERROR
  duration = (uint32)(dday * (int32)24*360000 + dtim);

RECOVER

ENDSEQ
  return(duration);

}

/******************************************************************************/
/**
\brief  operator-= - 


\return dbdatetime - 

\param  duration - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator-="

dttm &dttm :: operator-= (uint32 duration )
{
  int32  sec  = time.GetLongInt()/100 - duration;
  int32  sday = (int32)24*3600;
  uint16 dday = (uint16)(sec < 0 ? (-sec/sday)+1 : 0);
  date -= dday;
  time  = (dday*sday+sec)*100;
  return(*this);

}

/******************************************************************************/
/**
\brief  operator< - 


\return cond - Return value

\param  dbdatetime - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<"

logical dttm :: operator< (dttm dbdatetime )
{

  return (  date < dbdatetime.GetDate() ||
           (date == dbdatetime.GetDate() && time < dbdatetime.GetTime()) ); 


}

/******************************************************************************/
/**
\brief  operator<= - 


\return cond - Return value

\param  dbdatetime - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<="

logical dttm :: operator<= (dttm dbdatetime )
{

  return (  date  < dbdatetime.GetDate() ||
           (date == dbdatetime.GetDate() && time <= dbdatetime.GetTime()) ); 


}

/******************************************************************************/
/**
\brief  operator= - 


\return dbdatetime - 

\param  dbdatetime - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

dttm dttm :: operator= (dttm dbdatetime )
{

  date = dbdatetime.date.GetLongInt();
  time = dbdatetime.time;
  return(*this);
}

/******************************************************************************/
/**
\brief  operator== - 


\return cond - Return value

\param  dbdatetime - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical dttm :: operator== (dttm dbdatetime )
{

  return ( date == dbdatetime.GetDate() &&
           time == dbdatetime.GetTime()   );

}

/******************************************************************************/
/**
\brief  operator> - 


\return cond - Return value

\param  dbdatetime - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator>"

logical dttm :: operator> (dttm dbdatetime )
{

  return (  date  > dbdatetime.GetDate() ||
           (date == dbdatetime.GetDate() && time > dbdatetime.GetTime()) ); 


}

/******************************************************************************/
/**
\brief  operator>= - 


\return cond - Return value

\param  dbdatetime - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator>="

logical dttm :: operator>= (dttm dbdatetime )
{

  return (  date  > dbdatetime.GetDate() ||
           (date == dbdatetime.GetDate() && time >= dbdatetime.GetTime()) ); 


}

/******************************************************************************/
/**
\brief  ~dttm - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~dttm"

     dttm :: ~dttm ( )
{



}


