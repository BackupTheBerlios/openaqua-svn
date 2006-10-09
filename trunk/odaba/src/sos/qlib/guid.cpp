/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    guid

\brief    


\date     $Date: 2006/03/12 19:22:30,17 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "guid"

#include  <pdefault.h>
#include  <guidstr.h>
#include  <iNetConversion.h>
#include  <sdttm.hpp>
#include  <sguid.hpp>


/******************************************************************************/
/**
\brief  AutoCorrection


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AutoCorrection"

void guid :: AutoCorrection ( )
{

  if ( !memcmp(this,"                          ",sizeof(guid)) )
    memset(this,0,sizeof(guid));

}

/******************************************************************************/
/**
\brief  FromPIF


\param  convert -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

void guid :: FromPIF (logical convert )
{

BEGINSEQ
  if ( !convert )                                    LEAVESEQ
  
  time_stamp.FromPIF(YES);
  sid  = PIFToShort(sid,YES);
  num1 = PIFToShort(num1,YES);
  num2 = PIFToLong(num2,YES);

ENDSEQ

}

/******************************************************************************/
/**
\brief  GetSID

\return sid -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSID"

uint16 guid :: GetSID ( )
{

  return( this ? sid : UNDEF);

}

/******************************************************************************/
/**
\brief  GetString - 


\return guid_string -

\param  guid_string -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetString"

char *guid :: GetString (char *guid_string )
{
  __guid_string     *gs;
BEGINSEQ
  if ( !guid_string || sid == 0 )                      ERROR
  
  gs = (__guid_string *)guid_string;
  gs->id   = 'A';
  gs->sep0 = '-';
  gs->sep1 = '-';
  gs->sep2 = '-';
  gs->sep3 = '-';
  gs->sep4 = '-';
  gs->end  = 0;
  gvtxlth(gs->date,time_stamp.GetDate().GetLongInt());
  gvtxlth(gs->time,time_stamp.GetTime().GetLongInt());
  gvtxith(gs->sid,sid);
  gvtxith(gs->num1,num1);
  gvtxlth(gs->num2,num2);

RECOVER
  if ( guid_string )
    memset(guid_string,0,sizeof(__guid_string));
  guid_string = NULL;
ENDSEQ
  return(guid_string);
}

/******************************************************************************/
/**
\brief  Initialize - 


-------------------------------------------------------------------------------
\brief i00


\param  type_id
\param  number1 -
\param  number2 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void guid :: Initialize (uint16 type_id, uint32 number1, uint32 number2 )
{
//  extern    int32         guid_count;
//  extern    RessourceLock guid_lock;
  time_stamp.SetCurrent();
  sid  = type_id;
  num2 = number2;
  srand( number1 );
  num1 = rand();
  


}

/******************************************************************************/
/**
\brief i01


\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void guid :: Initialize (char *string )
{
  __guid_string     *gs = (__guid_string *)string;

  if ( (string[0] == '1' || string[0] == 'A') && 
       string[1] == '-' )                       // guid string
  {
    time_stamp.GetDate() = gvtxhtl(gs->date);
    time_stamp.GetTime() = gvtxhtl(gs->time);
    sid                  = gvtxhti(gs->sid);
    num1                 = gvtxhti(gs->num1);
    num2                 = gvtxhtl(gs->num2);
  }
  else
    memcpy(this,string,sizeof(guid));

}

/******************************************************************************/
/**
\brief  IsEmpty

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical guid :: IsEmpty ( )
{
  logical                 cond = YES;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
  if ( !memcmp(this,"                          ",sizeof(guid)) )
                                                     LEAVESEQ
  if ( !sid )                                        LEAVESEQ

  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  Reset - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void guid :: Reset ( )
{

  memset(this,0,sizeof(guid));

}

/******************************************************************************/
/**
\brief  ToPIF


\param  convert -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToPIF"

void guid :: ToPIF (logical convert )
{

BEGINSEQ
  if ( !convert )                                    LEAVESEQ
  
  time_stamp.ToPIF(YES);
  sid  = ShortToPIF(sid,YES);
  num1 = ShortToPIF(num1,YES);
  num2 = LongToPIF(num2,YES);

ENDSEQ

}

/******************************************************************************/
/**
\brief  guid

-------------------------------------------------------------------------------
\brief i0


\param  sid -
\param  number1 -
\param  number2 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "guid"

                        guid :: guid (int16 sid, uint32 number1, uint32 number2 )
                     : time_stamp(),
  sid(0),
  num1(0),
  num2(0)
{

  Initialize(sid,number1,number2);

}

/******************************************************************************/
/**
\brief i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "guid"

                        guid :: guid ( )
                     : time_stamp(),
  sid(0),
  num1(0),
  num2(0)
{



}


