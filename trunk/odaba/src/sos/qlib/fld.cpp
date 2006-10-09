/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    fld

\brief    


\date     $Date: 2006/06/13 22:32:42,37 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "fld"

#include  <pdefault.h>
#include  <csmcbdef.h>
#include  <sfmcb.hpp>
#include  <ssmcb.hpp>
#include  <sfld.hpp>


/******************************************************************************/
/**
\brief  AllocateArea - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AllocateArea"

logical fld :: AllocateArea ( )
{
  logical   term = NO;
BEGINSEQ
  if ( flddata && flddaloc )                         LEAVESEQ
  
  if ( fldfmcb )
  {
//  if ( fldfmcb->fmcbityp==-99 )                    SOSERR(99)
    if ( !SetArea((char *)fldfmcb->AllocateArea()) ) SOSERR(95)
    flddaloc = YES;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AllocateFMCB - 


\return fmcbptr - Field definition block

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AllocateFMCB"

fmcb *fld :: AllocateFMCB ( )
{

BEGINSEQ
  if ( !SetFMCB(new fmcb()) )                      SOSERR(95)
  fldfaloc = YES;

RECOVER

ENDSEQ
  return(fldfmcb);

}

/******************************************************************************/
/**
\brief  CreateStructFMCB - 


\return term - Success

\param  fldnames - Field name
\param  smcbptr - Structure definition block
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateStructFMCB"

logical fld :: CreateStructFMCB (char *fldnames, smcb *smcbptr )
{

  return ( fldsfmcb(fldnames,smcbptr) );

}

/******************************************************************************/
/**
\brief  GetArea - 


\return datarea - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetArea"

char *fld :: GetArea ( )
{

  return (flddata);

}

/******************************************************************************/
/**
\brief  GetChar - 


\return charval - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetChar"

char fld :: GetChar ( )
{

  return ( fldfmcb && flddata ? *GetArea() : ' ' );


}

/******************************************************************************/
/**
\brief  GetDate - 


\return dateval - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDate"

dbdt fld :: GetDate ( )
{
  dbdt   date_val;
  fld    datefld(fmcb::GetStaticFMCB(T_DATE),(char *)&date_val);
  if ( fldfmcb && flddata )
    datefld = *this;


  return(date_val);

}

/******************************************************************************/
/**
\brief  GetDateTime - 


\return datetimeval - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDateTime"

dttm fld :: GetDateTime ( )
{
  dttm   datetime_val;
//  fld    datetimefld(fmcb::GetStaticFMCB(T_DATETIME),(char *)&datetime_val);
  if ( fldfmcb && flddata )
//    datetimefld = *this;  später Variante mit Konvertierung
    if ( fldfmcb->fmcbityp == T_DATETIME )
      datetime_val = *(dttm *)flddata;


  return(datetime_val);

}

/******************************************************************************/
/**
\brief  GetDouble - 


\return dblval - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDouble"

double fld :: GetDouble ( )
{
  double    real_val = 0.0;
  fld       realfld(fmcb::GetStaticFMCB(T_REAL),(char *)&real_val);
  if ( fldfmcb && flddata )
    realfld = *this;


  return(real_val);
}

/******************************************************************************/
/**
\brief  GetFMCB - 


\return fmcbptr - Field definition block

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFMCB"

fmcb *fld :: GetFMCB ( ) const
{


  return(fldfmcb);
}

/******************************************************************************/
/**
\brief  GetField - 


\return fldenty - 

\param  fldnames - Field name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetField"

fld fld :: GetField (char *fldnames )
{
  fld       fldenty;
  if ( fldfmcb->fmcbsmcb )
    return( fldfmcb->fmcbsmcb->GetField(fldnames,flddata) );


  return(fldenty);

}

/******************************************************************************/
/**
\brief  GetInt - 


\return sintval - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInt"

int16 fld :: GetInt ( )
{

  return ( GetLong() );


}

/******************************************************************************/
/**
\brief  GetLong - 


\return longval - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLong"

int32 fld :: GetLong ( )
{
  int32     int_val = 0;
  fld       intfld(fmcb::GetStaticFMCB(T_INT),(char *)&int_val);

  if ( fldfmcb && flddata )
    intfld = *this;


  return(int_val);
}

/******************************************************************************/
/**
\brief  GetNormalized - 


\return longval - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNormalized"

int32 fld :: GetNormalized ( )
{

  return( flddata && fldfmcb->fmcbdim 
          ? fldfmcb->fmcbligt(flddata) 
          : ULONGMAX );


}

/******************************************************************************/
/**
\brief  GetNormalizedU - 


\return luval - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNormalizedU"

uint32 fld :: GetNormalizedU ( )
{

  return( flddata && fldfmcb->fmcbdim 
          ? fldfmcb->fmcblugt(flddata) 
          : ULONGMAX );


}

/******************************************************************************/
/**
\brief  GetSMCB - 


\return smcbptr - Structure definition block

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSMCB"

smcb *fld :: GetSMCB ( )
{

  return ( fldfmcb ? fldfmcb->fmcbsmcb : NULL );


}

/******************************************************************************/
/**
\brief  GetTime - 


\return timeval - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTime"

dbtm fld :: GetTime ( )
{
  dbtm   time_val;  // war (0L) fuer ini vor zuweisung, aber ohne fuer fehlerfall
  fld    timefld(fmcb::GetStaticFMCB(T_TIME),(char *)&time_val);

  if ( fldfmcb && flddata )
    timefld = *this;


  return(time_val);

}

/******************************************************************************/
/**
\brief  InitString - 


\return term - Success

\param  string - String value
\param  len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitString"

logical fld :: InitString (char *string, size_t len )
{
  logical      term = NO;
BEGINSEQ
  SetFMCB(new fmcb(*fmcb::GetStaticFMCB(T_STRING)));
  fldfaloc = YES;
  fldfmcb->fmcbbyte = (fldfmcb->fmcbsize = len) +1;
  flddata  = string;
    
  if ( !string )  
  {
    if ( AllocateArea() )                           ERROR
    *flddata = 0;
  }

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

void fld :: Initialize ( )
{

BEGINSEQ
  if ( fldfmcb ) 
  {
    if ( !flddata )
    {
      if ( !(flddata = (char *)fldfmcb->AllocateArea()) )  ERROR
      flddaloc = YES;
    }  
    fldfmcb->fmcbiini(flddata);
  }

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  IsTrue - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsTrue"

logical fld :: IsTrue ( )
{
  logical   lo_val = NO;
  fld       lofld(fmcb::GetStaticFMCB(T_LO),(char *)&lo_val);
  if ( fldfmcb && flddata )
    lofld = *this;
  return(lo_val);
}

/******************************************************************************/
/**
\brief  NormalizedLong - 


\return longval - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NormalizedLong"

int32 fld :: NormalizedLong ( )
{

 return (*(int32 *)flddata);

}

/******************************************************************************/
/**
\brief  NormalizedLongPt - 


\return longval - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NormalizedLongPt"

int32 *fld :: NormalizedLongPt ( )
{

 return ((int32 *)flddata);

}

/******************************************************************************/
/**
\brief  NormalizedShort - 


\return sintval - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NormalizedShort"

int16 fld :: NormalizedShort ( )
{

 return (*(int16 *)flddata);

}

/******************************************************************************/
/**
\brief  NormalizedShortP - 


\return sintval - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NormalizedShortP"

int32 *fld :: NormalizedShortP ( )
{

 return ((int32 *)flddata);

}

/******************************************************************************/
/**
\brief  SetArea - 


\return datarea - 

\param  datarea - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetArea"

char *fld :: SetArea (char *datarea )
{

BEGINSEQ
  if ( flddata == datarea )                          LEAVESEQ
    
  if ( flddaloc )
    fmcb::FreeArea(&flddata);
//    msmfs((void **)&flddata);
//    delete flddata;
  flddaloc = NO;
  flddata = (char *)datarea;
ENDSEQ
  return(flddata);
}

/******************************************************************************/
/**
\brief  SetDouble - 



\param  dblval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDouble"

void fld :: SetDouble (double dblval )
{

  if ( fldfmcb->fmcbdim )
    memcpy(flddata,&dblval,fldfmcb->fmcbbyte/fldfmcb->fmcbdim);


}

/******************************************************************************/
/**
\brief  SetFMCB - 


\return fmcbptr - Field definition block

\param  fmcbptr - Field definition block
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFMCB"

fmcb *fld :: SetFMCB (fmcb *fmcbptr )
{

  if ( fldfaloc )
    delete fldfmcb;
  fldfaloc = NO;
  fldfmcb = fmcbptr;


  return(fldfmcb);

}

/******************************************************************************/
/**
\brief  SetNormalized - 



\param  longval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetNormalized"

void fld :: SetNormalized (int32 longval )
{

  if ( flddata && fldfmcb->fmcbdim )
    memcpy(flddata,&longval,fldfmcb->fmcbbyte/fldfmcb->fmcbdim);


}

/******************************************************************************/
/**
\brief  SetNormalizedU - 



\param  luval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetNormalizedU"

void fld :: SetNormalizedU (uint32 luval )
{

  if ( flddata && fldfmcb->fmcbdim )
    memcpy(flddata,&luval,fldfmcb->fmcbbyte/fldfmcb->fmcbdim);


}

/******************************************************************************/
/**
\brief  SetupLength - 


\return term - Success

\param  fldentyc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupLength"

logical fld :: SetupLength (const fld &fldentyc )
{
  ushort      len = fldfmcb->fmcbbyte;
BEGINSEQ
  fldfmcb->fmcblnu(fldentyc.fldfmcb,fldentyc.flddata);
  if ( flddata && len < fldfmcb->fmcbbyte && fldfmcb->fmcbvar )
  {
    SetArea(NULL);
    AllocateArea();
  }

  if ( flddata == NULL )
  {
    if ( !memcmp(fldentyc.fldfmcb->fmcbtype,fldfmcb->fmcbtype,ID_SIZE) && !fldentyc.flddaloc &&
         (fldentyc.fldfmcb->fmcbrlev == fldfmcb->fmcbrlev ||
          (fldentyc.fldfmcb->fmcbrlev <= 0 && fldentyc.fldfmcb->fmcbrlev > R_REFR &&
           fldfmcb->fmcbrlev <= 0 && fldfmcb->fmcbrlev > R_REFR) ) )
    {
      flddata = fldentyc.flddata;                         LEAVESEQ
    }
    AllocateArea();
  }

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  fld - 


-------------------------------------------------------------------------------
\brief  BigInt - 


\param  int64_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fld"

     fld :: fld (int64 int64_val )
                     :   fldfmcb(fmcb::GetStaticFMCB2(T_INT,17)),
  flddata(NULL),
  flddaloc(NO),
  fldfaloc(NO)
{

  if ( !AllocateArea() )
    *(int64 *)flddata = int64_val;

}

/******************************************************************************/
/**
\brief  Date - 


\param  datefld - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fld"

     fld :: fld (dbdt datefld )
                     :   fldfmcb(fmcb::GetStaticFMCB(T_DATE)),
  flddata(NULL),
  flddaloc(NO),
  fldfaloc(NO)

{

  if ( !AllocateArea() )
    *(dbdt *)flddata = datefld;


}

/******************************************************************************/
/**
\brief  Dummy - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fld"

     fld :: fld ( )
                     :   fldfmcb(NULL),
  flddata(NULL),
  flddaloc(NO), 
  fldfaloc(NO)

{



}

/******************************************************************************/
/**
\brief  FLD_LOG - 


\param  logval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fld"

     fld :: fld (logical logval )
                     :   fldfmcb(fmcb::GetStaticFMCB(T_LO)),
  flddata(NULL),
  flddaloc(NO),
  fldfaloc(NO)

{

  if ( !AllocateArea() )
    *(logical *)flddata = logval;

}

/******************************************************************************/
/**
\brief  FLD_SD - 


\param  smcbptr - Structure definition block
\param  fldnames - Field name
\param  entry_area - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fld"

     fld :: fld (smcb *smcbptr, char *fldnames, void *entry_area )
                     :   fldfmcb(NULL),
  flddata(NULL),
  flddaloc(NO),
  fldfaloc(NO)

{
  int32     offset  = 0;
  fmcb     *fmcbptr = NULL;
  if ( smcbptr && (fldfmcb = smcbptr->SearchField(fldnames,&offset)) )
  {
    if ( offset )
    {
      fmcbptr  = new fmcb();
      *fmcbptr = *fldfmcb;
      fmcbptr->fmcbopt = NO;
      fmcbptr->fmcbposn += offset;
      SetFMCB(fmcbptr);
      fldfaloc = YES;
    }
    if ( entry_area )
      flddata = (char *)entry_area + fldfmcb->fmcbposn;
  }


}

/******************************************************************************/
/**
\brief  FLD_STR - 


\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fld"

     fld :: fld (char *string )
                     :   fldfmcb(NULL),
  flddata(NULL),
  flddaloc(NO),
  fldfaloc(NO)

{

  InitString(string,string ? strlen(string) : 256);

}

/******************************************************************************/
/**
\brief  FLD_STRL - 


\param  string - String value
\param  len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fld"

     fld :: fld (char *string, size_t len )
                     :   fldfmcb(NULL),
  flddata(NULL),
  flddaloc(NO),
  fldfaloc(NO)
{

  InitString(string,len);

}

/******************************************************************************/
/**
\brief  FLD_TIM - 


\param  timefld - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fld"

     fld :: fld (dbtm timefld )
                     :   fldfmcb(fmcb::GetStaticFMCB(T_TIME)),
  flddata(NULL),
  flddaloc(NO),
  fldfaloc(NO)
{

  if ( !AllocateArea() )
    *(dbtm *)flddata = timefld;


}

/******************************************************************************/
/**
\brief  FieldDef - 


\param  fmcbptr - Field definition block
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fld"

     fld :: fld (fmcb *fmcbptr )
                     :   fldfmcb(fmcbptr),
  flddata(NULL),
  flddaloc(NO), 
  fldfaloc(NO)

{

  if ( fmcbptr && fmcbptr->fmcbityp != -99  )
  {
    flddata  = (char *)fmcbptr->AllocateArea();
    flddaloc = YES;
  }  


}

/******************************************************************************/
/**
\brief  Float - 


\param  dblval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fld"

     fld :: fld (double dblval )
                     :   fldfmcb(fmcb::GetStaticFMCB(T_REAL)),
  flddata(NULL),
  flddaloc(NO),
  fldfaloc(NO)

{

  if ( !AllocateArea() )
    *(double *)flddata = dblval;

}

/******************************************************************************/
/**
\brief  Instance - 


\param  fmcbptr - Field definition block
\param  entry_area - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fld"

     fld :: fld (fmcb *fmcbptr, void *entry_area )
                     :   fldfmcb(fmcbptr),
  flddata((char *)entry_area),
  flddaloc(NO),
  fldfaloc(NO)

{



}

/******************************************************************************/
/**
\brief  Integer - 


\param  intval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fld"

     fld :: fld (int32 intval )
                     :   fldfmcb(fmcb::GetStaticFMCB(T_INT)),
  flddata(NULL),
  flddaloc(NO),
  fldfaloc(NO)
{

  if ( !AllocateArea() )
    *(int32 *)flddata = intval;

}

/******************************************************************************/
/**
\brief  i0 - 


\param  fldentyc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fld"

     fld :: fld (const fld &fldentyc )
                     :   fldfmcb(fldentyc.fldfmcb),
  flddata(fldentyc.flddata),
  flddaloc(NO),
  fldfaloc(NO)
{



}

/******************************************************************************/
/**
\brief  i1 - 


\param  datetimeval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fld"

     fld :: fld (dttm datetimeval )
                     :   fldfmcb(fmcb::GetStaticFMCB(T_DATETIME)),
  flddata(NULL),
  flddaloc(NO),
  fldfaloc(NO)
{

  if ( !AllocateArea() )
    *(dttm *)flddata = datetimeval;


}

/******************************************************************************/
/**
\brief  fldcmp - 


\return cmpval - Comparision result

\param  fldenty - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fldcmp"

int fld :: fldcmp (fld &fldenty )
{
  int       cmpval = ERIC;
  fld       cmpfld;
BEGINSEQ
  SetupLength(fldenty);
  
  if ( fldenty.fldfmcb->fmcbityp != fldfmcb->fmcbityp  ||
       fldenty.fldfmcb->fmcbbyte != fldfmcb->fmcbbyte )
  {
    cmpfld.SetFMCB(fldfmcb);
    cmpfld.AllocateArea();
  }  
  cmpfld = fldenty;                                  SOSCERR

  cmpval = fldfmcb->fmcbicmp(cmpfld.fldfmcb,flddata,cmpfld.flddata);

RECOVER

ENDSEQ
  return(cmpval);

}

/******************************************************************************/
/**
\brief  fldfalos - 



\param  opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fldfalos"

void fld :: fldfalos (logical opt )
{

  fldfaloc = opt;


}

/******************************************************************************/
/**
\brief  fldfmcbx - 


\return term - Success

\param  fmcbptr - Field definition block
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fldfmcbx"

logical fld :: fldfmcbx (fmcb *fmcbptr )
{
  logical   term = NO;

BEGINSEQ

  if ( !(fldfmcb = new fmcb()) )                    SOSERR(95)
  *fldfmcb = *fmcbptr;

  fldfaloc = YES;

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  fldinit - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fldinit"

void fld :: fldinit ( )
{

  SetArea(NULL);
  SetFMCB(NULL);


}

/******************************************************************************/
/**
\brief  fldsfmcb - 


\return term - Success

\param  fldnames - Field name
\param  smcbptr - Structure definition block
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fldsfmcb"

logical fld :: fldsfmcb (char *fldnames, smcb *smcbptr )
{
  int8      max_aligned = 1;
  logical   term        = NO;

BEGINSEQ
  if ( !smcbptr )                                    ERROR

  if ( !(fldfmcb = new fmcb(fldnames,smcbptr->smcbname,smcbptr->smcbnsid,R_DIRECT,UNDEF,0,1)) )
                                                     SOSERR(95)
  fldfmcb->fmcbesu(smcbptr,UNDEF,DEFAULT_ALLIGNMENT,max_aligned);
  fldfaloc = YES;

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  operator() - 


\return fldenty - 

\param  instptr - Structured instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator()"

fld &fld :: operator() (char *instptr )
{

  SetArea(NULL);
  
  if ( fldfmcb && instptr )
    SetArea((char *)instptr + fldfmcb->fmcbposn);
  

  return(*this);

}

/******************************************************************************/
/**
\brief  operator= - 


\return fldenty - 
-------------------------------------------------------------------------------
\brief  BigInt - 


\param  int64_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

fld &fld :: operator= (int64 int64_val )
{

  *this = fld(int64_val);
  return(*this);


}

/******************************************************************************/
/**
\brief  Boolean - 


\param  logval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

fld &fld :: operator= (logical logval )
{

  *this = fld(logval);
  return(*this);


}

/******************************************************************************/
/**
\brief  Date - 


\param  dateval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

fld &fld :: operator= (dbdt dateval )
{

  *this = fld(dateval);

  return(*this);
}

/******************************************************************************/
/**
\brief  Field - 


\param  fldentyc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

fld &fld :: operator= (const fld &fldentyc )
{
  ushort    len;

BEGINSEQ
  SOSRESET

  if ( !fldentyc.fldfmcb )                           ERROR
  
  if ( fldfmcb == NULL )
  {
    if ( !fldentyc.fldfaloc )
      fldfmcb = fldentyc.fldfmcb;
    else 
      fldfmcbx(fldentyc.fldfmcb);
  }
  if ( fldfmcb->fmcbityp == T_VOID && fldfmcb->fmcbrlev <= 0 )
                                                     LEAVESEQ
  if ( fldfmcb->fmcbityp==-99 ) //eigentlich muesste Quelle noch auf Kompatibilitaet geprueft werden
  {
    SetArea(fldentyc.flddata);                       LEAVESEQ
  }

  if ( !fldentyc.flddata )
  {
    SetArea(NULL);                                   LEAVESEQ
  }

  SetupLength(fldentyc);
  if ( !flddata )                                    ERROR
  
  if ( fldentyc.flddata == flddata )                 LEAVESEQ

  fldfmcb->fmcbicvt(fldentyc.fldfmcb,flddata,fldentyc.flddata);
  SOSCERR

RECOVER

ENDSEQ
  return(*this);

}

/******************************************************************************/
/**
\brief  Float - 


\param  dblval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

fld &fld :: operator= (double dblval )
{

  *this = fld(dblval);
  return(*this);


}

/******************************************************************************/
/**
\brief  Integer - 


\param  intval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

fld &fld :: operator= (int32 intval )
{

  *this = fld(intval);
  return(*this);


}

/******************************************************************************/
/**
\brief  String - 


\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

fld &fld :: operator= (char *string )
{

  return(*this = fld(string));


}

/******************************************************************************/
/**
\brief  Time - 


\param  timeval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

fld &fld :: operator= (dbtm timeval )
{

  *this = fld(timeval);
  return(*this);


}

/******************************************************************************/
/**
\brief  Timestamp - 


\param  datetimeval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

fld &fld :: operator= (dttm datetimeval )
{

//  *this = fld(datetimeval); später Variante mit Konvertierung
//  return(*this);
  
  if ( fldfmcb && fldfmcb->fmcbityp == T_DATETIME )
  {
    if ( flddata )
      *(dttm *)flddata = datetimeval;
    else
      SetArea((char *)&datetimeval);  
  }
  return(*this);


}

/******************************************************************************/
/**
\brief  xxGetString - 


\return strval - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xxGetString"

char *fld :: xxGetString ( )
{
  static    fld  strfld("");

  if ( fldfmcb && flddata )
    strfld = *this;

  if (fldfmcb && flddata) return strfld.GetArea();
  else return "";
}

/******************************************************************************/
/**
\brief  ~fld - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~fld"

     fld :: ~fld ( )
{

  fldinit();


}


