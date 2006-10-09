/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    dfs

\brief    Data format specification


\date     $Date: 2006/06/27 17:23:38,29 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "dfs"

#include  <pdefault.h>
#include  <isosi.h>
#include  <cDataFormSpec.h>
#include  <sdfs.hpp>


/******************************************************************************/
/**
\brief  Change - 



\param  timefmt - 
\param  datefmt - 
\param  decpoint - 
\param  thopoint - 
\param  separate - 
\param  parenth - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Change"

void __cdecl dfs :: Change (int16 timefmt, int16 datefmt, char decpoint, char thopoint, char separate, char parenth )
{
  dfs *data_format = (dfs *)GetProcessVariable(PVN_SOSDataFormat);
  data_format->Set(timefmt,datefmt,decpoint,thopoint,separate,parenth);

}

/******************************************************************************/
/**
\brief  ChangeDate - 



\param  datefmt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeDate"

void __cdecl dfs :: ChangeDate (int16 datefmt )
{
  dfs *data_format = (dfs *)GetProcessVariable(PVN_SOSDataFormat);
  data_format->SetDate(datefmt);


}

/******************************************************************************/
/**
\brief  ChangeDecimal - 



\param  decpoint - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeDecimal"

void __cdecl dfs :: ChangeDecimal (char decpoint )
{
  dfs *data_format = (dfs *)GetProcessVariable(PVN_SOSDataFormat);
  data_format->SetDecimal(decpoint);


}

/******************************************************************************/
/**
\brief  ChangeLanguage - 



\param  language - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeLanguage"

void __cdecl dfs :: ChangeLanguage (int16 language )
{
  dfs *data_format = (dfs *)GetProcessVariable(PVN_SOSDataFormat);
  data_format->SetLanguage(language);

}

/******************************************************************************/
/**
\brief  ChangeParenthes - 



\param  parchar - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeParenthes"

void __cdecl dfs :: ChangeParenthes (char parchar )
{
  dfs *data_format = (dfs *)GetProcessVariable(PVN_SOSDataFormat);
  data_format->SetParenthes(parchar);

}

/******************************************************************************/
/**
\brief  ChangeSeparator - 



\param  separate - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeSeparator"

void __cdecl dfs :: ChangeSeparator (char separate )
{
  dfs *data_format = (dfs *)GetProcessVariable(PVN_SOSDataFormat);
  data_format->SetSeparator(separate);


}

/******************************************************************************/
/**
\brief  ChangeThousands - 



\param  thopoint - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeThousands"

void __cdecl dfs :: ChangeThousands (char thopoint )
{
  dfs *data_format = (dfs *)GetProcessVariable(PVN_SOSDataFormat);
  data_format->SetThousands(thopoint);


}

/******************************************************************************/
/**
\brief  ChangeTime - 



\param  timefmt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeTime"

void __cdecl dfs :: ChangeTime (int16 timefmt )
{
  dfs *data_format = (dfs *)GetProcessVariable(PVN_SOSDataFormat);
  data_format->SetTime(timefmt);


}

/******************************************************************************/
/**
\brief  GetDateFormat - 


\return datefmt - 
-------------------------------------------------------------------------------
\brief  i0 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDateFormat"

int16 __cdecl dfs :: GetDateFormat ( )
{
  dfs *data_format = (dfs *)GetProcessVariable(PVN_SOSDataFormat);
  return ( data_format->get_dfsfdate() );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDateFormat"

int16 __cdecl dfs :: GetDateFormat (char *string )
{

  if ( string && *string )
  {
    if ( strchr(string,'.') )
      return(DFS_TTMMJJ_punkt);  
  }
  
  return( GetDateFormat() );


}

/******************************************************************************/
/**
\brief  GetDecimal - 


\return decchar - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDecimal"

char __cdecl dfs :: GetDecimal ( )
{
  dfs *data_format = (dfs *)GetProcessVariable(PVN_SOSDataFormat);
  return(data_format->get_dfscdec());

}

/******************************************************************************/
/**
\brief  GetLanguage - 


\return language - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLanguage"

int16 __cdecl dfs :: GetLanguage ( )
{
  dfs *data_format = (dfs *)GetProcessVariable(PVN_SOSDataFormat);
  return( data_format->get_dfslang() );


}

/******************************************************************************/
/**
\brief  GetOffValue - 


\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOffValue"

char *__cdecl dfs :: GetOffValue ( )
{

  return("N");

}

/******************************************************************************/
/**
\brief  GetOnValue - 


\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOnValue"

char *__cdecl dfs :: GetOnValue ( )
{
  dfs *data_format = (dfs *)GetProcessVariable(PVN_SOSDataFormat);
  switch ( data_format->get_dfslang() )
  {
    case DFS_Deutsch : return("J");
    case DFS_English :
    default          : return("Y");
  }

}

/******************************************************************************/
/**
\brief  GetParenthesis - 


\return parstr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParenthesis"

char *__cdecl dfs :: GetParenthesis ( )
{
  dfs *data_format = (dfs *)GetProcessVariable(PVN_SOSDataFormat);
  return ( data_format->get_dfscpar() );

}

/******************************************************************************/
/**
\brief  GetSeparator - 


\return sepchar - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSeparator"

char __cdecl dfs :: GetSeparator ( )
{
  dfs *data_format = (dfs *)GetProcessVariable(PVN_SOSDataFormat);
  return( data_format->get_dfscsep() );


}

/******************************************************************************/
/**
\brief  GetTimeFormat - 


\return timefmt - 
-------------------------------------------------------------------------------
\brief  i0 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTimeFormat"

int16 __cdecl dfs :: GetTimeFormat ( )
{
  dfs *data_format = (dfs *)GetProcessVariable(PVN_SOSDataFormat);
  return ( data_format->get_dfsftime() );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTimeFormat"

int16 __cdecl dfs :: GetTimeFormat (char *string )
{
  int      len;
  short    timefmt = UNDF;
  if ( string && (len = strlen(string)) )
  {
    if ( len >= 8 )
      timefmt = DFS_HHMMSS;
    else if ( len >= 5 )
      timefmt = DFS_HHMM;
    else if ( len >= 2 )
      ;
//      timefmt = DFS_HH; das gibts leider noch nicht
  }
  return(timefmt);
}

/******************************************************************************/
/**
\brief  Set - 



\param  timefmt - 
\param  datefmt - 
\param  decpoint - 
\param  thopoint - 
\param  separate - 
\param  parenth - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Set"

void dfs :: Set (int16 timefmt, int16 datefmt, char decpoint, char thopoint, char separate, char parenth )
{

  if ( datefmt )
    dfsfdate  = datefmt;
  if ( timefmt )
    dfsftime  = timefmt;
  if ( decpoint )
    dfscdec  = decpoint;
  if ( thopoint )
    dfscthou = thopoint;
  if ( separate )
    dfscsep  = separate;
  if ( parenth )
    SetParenthes(parenth);


}

/******************************************************************************/
/**
\brief  SetDate - 



\param  datefmt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDate"

void dfs :: SetDate (int16 datefmt )
{

  dfsfdate = datefmt;


}

/******************************************************************************/
/**
\brief  SetDecimal - 



\param  decpoint - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDecimal"

void dfs :: SetDecimal (char decpoint )
{

  dfscdec  = decpoint;


}

/******************************************************************************/
/**
\brief  SetLanguage - 



\param  language - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLanguage"

void dfs :: SetLanguage (int16 language )
{

  switch ( language )
  {
    case DFS_Deutsch : dfslang  = DFS_Deutsch;
                       dfsfdate = DFS_TTMMJJ_punkt;
                       dfsftime = DFS_HHMMSS;
                       dfscdec  = ',';
                       dfscthou = '.';
                       dfscsep  = '|';
                       SetParenthes('{');
                       break;
    default          : dfslang  = DFS_English;
                       dfsfdate = DFS_YYMMDD_slash;
                       dfsftime = DFS_HHMMSS;
                       dfscdec  = '.';
                       dfscthou = ',';
                       dfscsep  = '|';
                       SetParenthes('{');
  }


}

/******************************************************************************/
/**
\brief  SetParenthes - 



\param  parchar - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetParenthes"

void dfs :: SetParenthes (char parchar )
{
  char      cp;
  switch ( parchar ) 
  {
    case '(' : cp = ')';                                   break;
    case '[' : cp = ']';                                   break;
    case '{' : cp = '}';                                   break;
    case '<' : cp = '>';                                   break;
    case '®' : cp = '¯';                                   break;
    default  : parchar = '('; cp = ')';
  }
  dfscpar[0] = parchar;
  dfscpar[1] = cp;


}

/******************************************************************************/
/**
\brief  SetSeparator - 



\param  separate - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSeparator"

void dfs :: SetSeparator (char separate )
{

  dfscsep  = separate;


}

/******************************************************************************/
/**
\brief  SetThousands - 



\param  thopoint - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetThousands"

void dfs :: SetThousands (char thopoint )
{

  dfscthou = thopoint;


}

/******************************************************************************/
/**
\brief  SetTime - 



\param  timefmt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTime"

void dfs :: SetTime (int16 timefmt )
{

  dfsftime  = timefmt;


}

/******************************************************************************/
/**
\brief  dfs - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dfs"

     dfs :: dfs ( )
{

  dfslang    = DFS_English;
  dfsfdate   = DFS_YYMMDD_slash;
  dfsftime   = DFS_HHMMSSHH;
  dfscdec    = '.';
  dfscthou   = ',';
  dfscsep    = '|';
  dfscpar[0] = '{';
  dfscpar[1] = '}';


}


