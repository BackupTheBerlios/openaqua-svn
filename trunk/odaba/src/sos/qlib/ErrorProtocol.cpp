/********************************* Class Source Code ***************************/
/**
\package  SOS
\class    ErrorProtocol



\date     $Date: 2006/04/26 21:16:31,64 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ErrorProtocol"

#include  <pdefault.h>
#include  <sErrorProtocol.hpp>


/******************************************************************************/
/**
\brief  ErrorProtocol

-------------------------------------------------------------------------------
\brief  i00


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ErrorProtocol"

                        ErrorProtocol :: ErrorProtocol ( )
                     : NString(),
Error(),
  warning_level(0),
  msg_indent(0),
  message()
{
}

/******************************************************************************/
/**
\brief  i02


\param  err_obj - Error object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ErrorProtocol"

                        ErrorProtocol :: ErrorProtocol (Error &err_obj )
                     : NString(),
Error(err_obj),
  warning_level(0),
  msg_indent(0),
  message()
{
}

/******************************************************************************/
/**
\brief  SetMessageIndent


\param  indent
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMessageIndent"

void ErrorProtocol :: SetMessageIndent (uint16 indent )
{

  msg_indent = indent;

}

/******************************************************************************/
/**
\brief  SetWarningLevel


\param  wlevel
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWarningLevel"

void ErrorProtocol :: SetWarningLevel (int8 wlevel )
{

  warning_level = wlevel;

}

/******************************************************************************/
/**
\brief  WarningLevel

\return wlevel

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WarningLevel"

int8 ErrorProtocol :: WarningLevel ( )
{

  return(warning_level);

}

/******************************************************************************/
/**
\brief  Write

\return term - Success
-------------------------------------------------------------------------------
\brief  i00


\param  err_code - Error code
\param  wlevel
\param  errvar1 - First error variable
\param  errvar2 - Second error variable
\param  errvar3 - Third error variable
\param  errvar4 - Fourth error variable
\param  errvar5 - Fifth error variable
\param  errvar6 - Sixth error variable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Write"

logical ErrorProtocol :: Write (const int16 err_code, int8 wlevel, char *errvar1, char *errvar2, char *errvar3, char *errvar4, char *errvar5, char *errvar6 )
{
  logical      term = NO;
BEGINSEQ
  if ( wlevel > warning_level )                     LEAVESEQ
  
  GetErrorText(NULL,err_code,errvar1,errvar2,errvar3,errvar4,errvar5,errvar6);
  error = err_code;
  message.SetData(this);
  
  Append(' ',msg_indent);
  Append(message.component,sizeof(message.component));
  Append(' ');
  Append(message.error_type,sizeof(message.error_type));
  Append(' ');
  Append(message.error_code,sizeof(message.error_code));
  Append(':');
  Append(' ');
  Append(message.text,sizeof(message.text));
  Append("\n",0);

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01


\param  text - Error text
\param  wlevel
\param  text_type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Write"

logical ErrorProtocol :: Write (char *text, int8 wlevel, char *text_type )
{
  char      string[sizeof(message.component)+1];
  logical   term = NO;
BEGINSEQ
  if ( wlevel > warning_level )                     LEAVESEQ
  
  error = UNDEF;
  message.SetData(this);
  
  Append(' ',msg_indent);
  Append(' ',strlen(gvtxbts(string,message.component,sizeof(message.component))));
  Append(' ');
  Append(text_type);
  Append(' ');
  Append(' ',sizeof(message.error_code));
  Append(':');
  Append(' ');
  Append(text,0);
  Append("\n",0);

ENDSEQ
  return(term);
}


