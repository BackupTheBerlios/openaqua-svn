/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    dbdt

\brief    


\date     $Date: 2006/07/21 12:35:10,76 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "dbdt"

#include  <dosdt.h>
#include  <pdefault.h>
#include  <cdbdt.h>
#include  <cDataFormSpec.h>
#include  <iNetConversion.h>
#include  <sdfs.hpp>
#include  <sfld.hpp>
#include  <sdbdt.hpp>


/******************************************************************************/
/**
\brief  FromPIF - 



\param  convert - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

void dbdt :: FromPIF (logical convert )
{

  dbdtdate = PIFToLong(dbdtdate,convert);

}

/******************************************************************************/
/**
\brief  FromString - 


\return date - 

\param  string - String value
\param  size - 
\param  date_format - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromString"

dbdt dbdt :: FromString (char *string, uint16 size, int32 date_format )
{
  char          wstring[16];
  char         *strptr = wstring;
  ushort        pos;             
  int16         hyear  = 0;
  int16         year   = 0;
  int16         mon    = 0;
  int16         day    = 0;
  char          dstring[17];

  memset(wstring,0,sizeof(wstring));

  if ( !string )
    SetDate();
  else
  {
    memset(wstring,0,sizeof(wstring));
    gvtxbts(dstring,string,MIN(size,sizeof(dstring)-1));

    if ( date_format == DFS_Default )
      date_format = dfs::GetDateFormat();
    switch ( date_format )
    {
      case DFS_TTMMJJ_punkt   :
      case DFS_TTMMJJJJ_punkt :
        switch ( size )
        {
          case 5  : mon   = atoi((char *)memcpy(wstring,string+size-5,2));
          case 2  : year  = atoi((char *)memcpy(wstring,string+size-2,2));
                    year += (year < 70 ? 2000 : 1900);
                    break;
          default : memcpy(wstring,string,MIN(10,size));
                    day  = atoi(wstring);
                    if ( (pos = strspn(strptr,"0123456789")) < strlen(strptr) )
                    {
                      mon     = atoi(strptr+=pos+1);
                      if ( (pos = strspn(strptr,"0123456789")) < strlen(strptr) )
                        if ( (year = atoi(strptr+pos+1)) < 100 )
                          year += (year < 70 ? 2000 : 1900);
                     }
        }
        break;
      case DFS_YYMMDD_slash   :
      case DFS_YYMMDD_point   :
        switch ( size )
        {
          case 5  : mon   = atoi((char *)memcpy(wstring,string+size-2,2));
          case 2  : year  = atoi((char *)memcpy(wstring,string,2));
                    year += (year < 70 ? 2000 : 1900);
                    break;
          default : memcpy(wstring,string,MIN(10,size));
                    if ( (year = atoi(wstring)) < 100 )
                      year += (year < 70 ? 2000 : 1900);
                    if ( (pos = strspn(strptr,"0123456789")) < strlen(strptr) )
                    {
                      mon     = atoi(strptr+=pos+1);
                      if ( (pos = strspn(strptr,"0123456789")) < strlen(strptr) )
                        day = atoi(strptr+pos+1);
                    }
        }
        break;
      case DFS_TTMMJJ         :
      case DFS_TTMMJJJJ       :
        pos = 0;
        switch ( size )
        {
          case 8  : hyear = atoi((char *)memcpy(wstring,string+4,2)) * 100;
          case 6  : day   = atoi((char *)memcpy(wstring,string,2));
                    pos   = 2;
          case 4  : mon   = atoi((char *)memcpy(wstring,string+pos,2));
          case 2  : year  = atoi((char *)memcpy(wstring,string+size-2,2));
                    year += (size == 8 ? hyear : year < 70 ? 2000 : 1900);
          default : ;
        }
        break;
      case DFS_YYMMDD         :
      case DFS_YYYYMMDD       :
        pos = 0;
        switch ( size )
        {
          case 8  : hyear = atoi((char *)memcpy(wstring,string,2)) * 100;
          case 6  : day   = atoi((char *)memcpy(wstring,string+size-2,2));
                    pos   = 2;
          case 4  : mon   = atoi((char *)memcpy(wstring,string+size-2-pos,2));
          case 2  : year  = atoi((char *)memcpy(wstring,string,2));
                    year += (size == 8 ? hyear : year < 70 ? 2000 : 1900);
          default : ;
        }
        break;
      case DFS_Default        : 
      default                 : ;
    }
    dbdtdate = dbdtlst(day,mon,year);
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

logical dbdt :: FromUnix (int64 unixtimestamp )
{
  logical      term = NO;
  tm           *time;
  time = localtime((time_t*)&unixtimestamp);
  dbdtlst(time->tm_mday,time->tm_mon+1,
          time->tm_year+1900+(time->tm_year < 99 ? 100 : 0));

  return(term);
}

/******************************************************************************/
/**
\brief  GetDay - 


\return day - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDay"

uint16 dbdt :: GetDay ( )
{
  uint16 day;
  uint16 month;
  uint16 year;
  GetDayMonthYear(&day,&month,&year);

  return(day);
}

/******************************************************************************/
/**
\brief  GetDayMonthYear - 



\param  day_ptr - 
\param  month_ptr - 
\param  year_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDayMonthYear"

void dbdt :: GetDayMonthYear (uint16 *day_ptr, uint16 *month_ptr, uint16 *year_ptr )
{

  dbdtlgt(day_ptr,month_ptr,year_ptr);

}

/******************************************************************************/
/**
\brief  GetDecade - 


\return decade - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDecade"

uint16 dbdt :: GetDecade ( )
{
  int32       days;
  days = dbdtdate - dbdt(1,GetMonth(),GetYear()).GetLongInt();
  return( MIN(2,days/10)+1 );

}

/******************************************************************************/
/**
\brief  GetLongInt - 


\return datval - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLongInt"

int32 dbdt :: GetLongInt ( )
{

 return ( IsEmpty() ? 0 : dbdtdate );

}

/******************************************************************************/
/**
\brief  GetMonth - 


\return month - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMonth"

uint16 dbdt :: GetMonth ( )
{
  uint16 day;
  uint16 month;
  uint16 year;
  GetDayMonthYear(&day,&month,&year);
  return(month);

}

/******************************************************************************/
/**
\brief  GetWeekDay - 


\return day - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetWeekDay"

uint16 dbdt :: GetWeekDay ( )
{
  int32       days;
  days = dbdtdate - dbdt(1,1,1990).GetLongInt();
  return( days%7+1 );

}

/******************************************************************************/
/**
\brief  GetYear - 


\return year - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetYear"

uint16 dbdt :: GetYear ( )
{
  uint16 day;
  uint16 month;
  uint16 year;
  GetDayMonthYear(&day,&month,&year);
  return(year);

}

/******************************************************************************/
/**
\brief  IsEmpty - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical dbdt :: IsEmpty ( )
{

  return ( dbdtdate <= 1 ? YES : NO );

}

/******************************************************************************/
/**
\brief  MinusMonth - 


\return dbdate - 

\param  month_count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MinusMonth"

dbdt &dbdt :: MinusMonth (uint16 month_count )
{
  uint16           oday;
  uint16           omonth;
  uint16           oyear;
  logical          lastday;

BEGINSEQ
  if ( IsEmpty() )                                   ERROR
  dbdtlgt(&oday,&omonth,&oyear);

  if ( oyear < 1870 || (12*(oyear-1870) + omonth) <= month_count )
                                                     ERROR
  lastday = (oday == (ushort)mday[omonth-1] ? YES : NO);
  
  while ( omonth <= month_count )
  {
    month_count -= omonth;
    omonth = 12;
    --oyear;
  }

  omonth -= month_count;
  oday    = lastday ? mday[omonth-1] : MIN(oday,(ushort)mday[omonth-1]);

RECOVER
  oday   = 0;
  omonth = 0;
  oyear  = 0;
ENDSEQ
  dbdtlst(oday,omonth,oyear);
  return(*this);

}

/******************************************************************************/
/**
\brief  MinusYear - 


\return dbdate - 

\param  year_count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MinusYear"

dbdt &dbdt :: MinusYear (uint16 year_count )
{
  uint16           oday;
  uint16           omonth;
  uint16           oyear;
  logical          lastday;

BEGINSEQ
  if ( IsEmpty() )                                   ERROR
  dbdtlgt(&oday,&omonth,&oyear);
  oyear -= year_count;

RECOVER
  oday   = 0;
  omonth = 0;
  oyear  = 0;
ENDSEQ
  dbdtlst(oday,omonth,oyear);
  return(*this);

}

/******************************************************************************/
/**
\brief  PlusMonth - 


\return dbdate - 

\param  month_count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PlusMonth"

dbdt &dbdt :: PlusMonth (uint16 month_count )
{
  uint16           oday;
  uint16           omonth;
  uint16           oyear;
  logical          lastday;

BEGINSEQ
  if ( IsEmpty() )                                   ERROR
  dbdtlgt(&oday,&omonth,&oyear);
  lastday = (oday == (ushort)mday[omonth-1] ? YES : NO);

  while ( omonth + month_count > 12 )
  {
    month_count -= (13-omonth);
    omonth = 1;
    ++oyear;
  }

  omonth += month_count;
  oday    = lastday ? mday[omonth-1] : MIN(oday,(ushort)mday[omonth-1]);

RECOVER
  oday   = 0;
  omonth = 0;
  oyear  = 0;
ENDSEQ
  dbdtlst(oday,omonth,oyear);
  return(*this);

}

/******************************************************************************/
/**
\brief  PlusYear - 


\return dbdate - 

\param  year_count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PlusYear"

dbdt &dbdt :: PlusYear (uint16 year_count )
{
  uint16           oday;
  uint16           omonth;
  uint16           oyear;
  logical          lastday;

BEGINSEQ
  if ( IsEmpty() )                                   ERROR
  dbdtlgt(&oday,&omonth,&oyear);
  oyear += year_count;

RECOVER
  oday   = 0;
  omonth = 0;
  oyear  = 0;
ENDSEQ
  dbdtlst(oday,omonth,oyear);
  return(*this);

}

/******************************************************************************/
/**
\brief  SetDate - 


\return dbdtptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDate"

dbdt &dbdt :: SetDate ( )
{
#if defined (WIN32) || defined (__unix__)
//  time_t ltime;
  _timeb  ltime;
  tm     *tm_ptr;
#else
  DOS_DATE cdate;
#endif

  dbdtdate = 0;

#if defined (WIN32) || defined (__unix__)
  _ftime(&ltime);
  tm_ptr = localtime(&(ltime.time));
//  time(&ltime);
//  tm_ptr = gmtime(&ltime);
  dbdtlst(tm_ptr->tm_mday,tm_ptr->tm_mon+1,
          tm_ptr->tm_year+1900+(tm_ptr->tm_year < 99 ? 100 : 0));
#else
  _dos_getdate(&cdate);
  dbdtlst(cdate.day,cdate.month,cdate.year);
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

void dbdt :: ToPIF (logical convert )
{

  dbdtdate = LongToPIF(dbdtdate,convert);

}

/******************************************************************************/
/**
\brief  ToString - 


\return string - String value

\param  string - String value
\param  size - 
\param  date_format - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToString"

char *dbdt :: ToString (char *string, uint16 size, int32 date_format )
{
  uint16    day;
  uint16    mon;
  uint16    year;
  int16     point = 0;
  memset(string,0,size+1);
  if ( GetLongInt() )
  {
    memcpy(string,"99999999",size);
    GetDayMonthYear(&day,&mon,&year);

    if ( date_format == DFS_Default )
      date_format = dfs::GetDateFormat();
    switch ( date_format )
    {
      case DFS_YYMMDD_slash :
      case DFS_YYMMDD_point : point = 1;
      case DFS_YYYYMMDD       :
      case DFS_YYMMDD       :
        if ( point )
          memcpy(string,
                 (date_format == DFS_YYMMDD_point ? "9999.99.99" : "9999/99/99")+10-size,
                 size);
        switch ( MIN(8,size-point*(1+(size>6))) )
        {
          case 8 : gvtxitp(string,year,4);
                   gvtxitp(string+4+point,mon,2);
                   gvtxltp(string+6+2*point,day,2);
                   break;
          case 7 :
          case 6 : gvtxltp(string,year%100,2);
          case 5 :
          case 4 : gvtxitp(string+size-4-point,mon,2);
          case 3 :
          case 2 : gvtxitp(string+size-2,day,2);
        }
        break;
        
      case DFS_TTMMJJJJ_punkt : 
      case DFS_TTMMJJ_punkt   : point = 1;
      case DFS_TTMMJJJJ       :
      case DFS_TTMMJJ         :
        if ( point )
          memcpy(string,"99.99.9999",size);
        switch ( MIN(8,size-point*(1+(size>6))) )
        {
          case 8 : gvtxitp(string+4+2*point,year,4);
                   gvtxitp(string+2+point,mon,2);
                   gvtxltp(string,day,2);
                   break;
          case 7 :
          case 6 : gvtxltp(string,day,2);
          case 5 :
          case 4 : gvtxitp(string+size-4-point,mon,2);
          case 3 :
          case 2 : gvtxitp(string+size-2,year%100,2);
        }
        break;
    }
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

int64 dbdt :: ToUnix ( )
{
  int64      stamp = -1;
  tm time;
  uint16 day;
  uint16 month;
  uint16 year;
  GetDayMonthYear(&day,&month,&year);
  // return seconds since 1.1.1970
	time.tm_sec = 0;
	time.tm_min = 0;
	time.tm_hour = 0;
	time.tm_mday = day;
	time.tm_mon = month;
	time.tm_year = year - 1900;
    stamp = (int64) ::mktime(&time);
  return(stamp);
}

/******************************************************************************/
/**
\brief  dbdt - 


-------------------------------------------------------------------------------
\brief  DBDT_ - 


\param  datval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbdt"

     dbdt :: dbdt (int32 datval )
{

  memcpy(&dbdtdate,&datval,sizeof(dbdt));

}

/******************************************************************************/
/**
\brief  DBDT_S - 


\param  day - 
\param  month - 
\param  year - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbdt"

     dbdt :: dbdt (uint16 day, uint16 month, uint16 year )
                     : dbdtdate(dbdtlst(day,month,year))

{



}

/******************************************************************************/
/**
\brief  dbdtlgt - 



\param  day_ptr - 
\param  month_ptr - 
\param  year_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbdtlgt"

void dbdt :: dbdtlgt (uint16 *day_ptr, uint16 *month_ptr, uint16 *year_ptr )
{
  int32    lday;

BEGINSEQ
  *day_ptr = *month_ptr = *year_ptr = 0;
  if ( IsEmpty() )                                   LEAVESEQ

  for ( lday  = dbdtdate%(365*4+1), *year_ptr = (ushort)(1870 + dbdtdate/(365*4+1)*4);
        lday > 365 + !((*year_ptr)%4) ;
	lday -= (365 + !((*year_ptr)%4) ), (*year_ptr)++ ) ;

  if ( !lday && dbdtdate )
  {
    (*year_ptr)--;
    lday = 365;
  }
  mday[1] = 28 + !(*year_ptr%4);

  for( *month_ptr=1; lday > mday[(*month_ptr)-1]; lday -= mday[(*month_ptr)-1], (*month_ptr)++ ) ;

  *day_ptr = (uint16)lday;

ENDSEQ

}

/******************************************************************************/
/**
\brief  dbdtlst - 


\return datval - 

\param  day - 
\param  month - 
\param  year - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbdtlst"

int32 dbdt :: dbdtlst (uint16 day, uint16 month, uint16 year )
{

  static short int mon[12] = {   0,  31,  59,  90, 120, 151,
		               181, 212, 243, 273, 304, 334, };

  if ( month < 1    || month > 12 ||
       day   < 1    || day   > 31 ||
       year  < 1870                  )
    dbdtdate = UNDEF;
  else     
    dbdtdate = (year-1870)*365 + (year-1869)/4              +
                mon[month-1] + ( !(year%4)  &&  month > 2 ) +
	        day;
  if ( dbdtdate == 1 )  // 1.1.1870 is empty
    dbdtdate = 0;
    
  return(dbdtdate);


}

/******************************************************************************/
/**
\brief  operator!= - 


\return cond - Return value

\param  dbdate - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!="

logical dbdt :: operator!= (dbdt dbdate )
{

  return ( dbdtdate != dbdate.GetLongInt() );

}

/******************************************************************************/
/**
\brief  operator+ - 


\return dbdate - 

\param  days - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+"

dbdt dbdt :: operator+ (int32 days )
{

  return ( dbdt(dbdtdate+days) );


}

/******************************************************************************/
/**
\brief  operator+= - 


\return dbdate - 

\param  days - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+="

dbdt dbdt :: operator+= (int32 days )
{

  dbdtdate += days;
  return(*this);
}

/******************************************************************************/
/**
\brief  operator- - 


\return dbdate - 

\param  days - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator-"

dbdt dbdt :: operator- (int32 days )
{

  return ( dbdt(dbdtdate > days ? dbdtdate-days : 0) );


}

/******************************************************************************/
/**
\brief  operator-= - 


\return dbdate - 

\param  days - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator-="

dbdt dbdt :: operator-= (int32 days )
{

  dbdtdate -= days;
  return(*this);
}

/******************************************************************************/
/**
\brief  operator< - 


\return cond - Return value

\param  dbdate - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<"

logical dbdt :: operator< (dbdt dbdate )
{

  return ( dbdtdate < dbdate.GetLongInt() );

}

/******************************************************************************/
/**
\brief  operator<= - 


\return cond - Return value

\param  dbdate - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<="

logical dbdt :: operator<= (dbdt dbdate )
{

  return ( dbdtdate <= dbdate.GetLongInt() );

}

/******************************************************************************/
/**
\brief  operator= - 


\return dbdate - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  days - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

dbdt dbdt :: operator= (int32 days )
{

  dbdtdate = days > 1 ? days : 0;

  return(*this);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

dbdt dbdt :: operator= (char *string )
{
  fld          date_fld(*this);
  fld          string_fld(string);
  date_fld.SetArea((char *)this);
  date_fld = string_fld;
  
  if ( dbdtdate <= 1 )
    dbdtdate = 0;
  return(*this);
}

/******************************************************************************/
/**
\brief  operator== - 


\return cond - Return value

\param  dbdate - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical dbdt :: operator== (dbdt dbdate )
{

  return ( dbdtdate == dbdate.GetLongInt() );

}

/******************************************************************************/
/**
\brief  operator> - 


\return cond - Return value

\param  dbdate - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator>"

logical dbdt :: operator> (dbdt dbdate )
{

  return ( dbdtdate > dbdate.GetLongInt() );

}

/******************************************************************************/
/**
\brief  operator>= - 


\return cond - Return value

\param  dbdate - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator>="

logical dbdt :: operator>= (dbdt dbdate )
{

  return ( dbdtdate >= dbdate.GetLongInt() );

}


