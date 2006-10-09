/********************************* Class Source Code ***************************/
/**
\package  OPS - 
\class    opsi

\brief    


\date     $Date: 2006/07/12 19:10:54,57 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "opsi"

#include  <pops7.h>
#include  <sErrorProtocol.hpp>
#include  <sPropertyHandle.hpp>

#include  <iopsi.h>

/******************************************************************************/
/**
\brief  SDBOutputMessage - 


\return string - 

\param  nstring - 
\param  clear_opt - 
\param  errcode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDBOutputMessage"

char *__cdecl SDBOutputMessage (NString &nstring, logical clear_opt, int errcode )
{

  return ( SDBOutputMessageParm(nstring,clear_opt,errcode,
                                NULL,NULL,NULL,NULL,NULL,NULL) );


}

/******************************************************************************/
/**
\brief  SDBOutputMessageParm - 


\return string - 

\param  nstring - 
\param  clear_opt - 
\param  errcode - 
\param  parm1 - 
\param  parm2 - 
\param  parm3 - 
\param  parm4 - 
\param  parm5 - 
\param  parm6 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDBOutputMessageParm"

char *__cdecl SDBOutputMessageParm (NString &nstring, logical clear_opt, int errcode, char *parm1, char *parm2, char *parm3, char *parm4, char *parm5, char *parm6 )
{
  ErrorMessage     err_message;
  if ( clear_opt )
    nstring = "";
    
  SDBError().GetErrorText(NULL,errcode,
                          parm1,parm2,parm3,
                          parm4,parm5,parm6);
                          
  SDBISET(errcode) 
  err_message.SetData(&SDBError());
  SDBRESET
  
  nstring.Append(err_message.component,sizeof(err_message.component));
  nstring += ' ';
  nstring.Append(err_message.error_type,sizeof(err_message.error_type));
  nstring += ' ';
  nstring.Append(err_message.error_code,sizeof(err_message.error_code));
  nstring += ':';
  nstring += ' ';
  nstring.Append(err_message.text,sizeof(err_message.text));
  nstring += "\n";

  return(nstring);
}

/******************************************************************************/
/**
\brief  SDBSetProperty - 


\return term - 

\param  prophdl - 
\param  propnames - 
\param  string - 
\param  protocol - 
\param  parm1 - 
\param  parm2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDBSetProperty"

logical __cdecl SDBSetProperty (PropertyHandle *prophdl, char *propnames, char *string, ErrorProtocol *protocol, char *parm1, char *parm2 )
{
  PropertyHandle   *ph   = prophdl->GPH(propnames);
  NString           text;
  logical           term = NO;
BEGINSEQ
  if ( !ph )
  {
    SDBOutputMessage(*protocol,NO,0);
    ERROR
  }

  if ( *ph == string )                              LEAVESEQ
  
  if ( parm1 )
  {
    text += parm1;
    text.Append(" - ");
  }
  text += "'";
  text += propnames;
  text += "' changed to '";
  text += string;
  text += "'";

  if ( parm2 )
  {
    text += " (";
    text += parm2;
    text += ")";
  }

  protocol->Write(text,2,"Info ");

  *ph = string;
  if ( SDBERROR ) 
  {
    SDBOutputMessage(*protocol,NO,0);
    ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

