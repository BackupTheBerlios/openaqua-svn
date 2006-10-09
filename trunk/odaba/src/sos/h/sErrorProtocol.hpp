/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/05|16:41:32,95}|(REF)
\class    ErrorProtocol



\date     $Date: 2006/04/20 13:39:45,04 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ErrorProtocol_HPP
#define   ErrorProtocol_HPP

class     ErrorProtocol;
#include "csosdll.h"

#include  <sError.hpp>
#include  <sErrorMessage.hpp>
#include  <sNString.hpp>
class  ErrorProtocol :public NString,
public Error
{
protected  :         int8                                         warning_level ATTR_ALIGN(4);                               
protected  :         int8                                         msg_indent;                                                
protected  :         ErrorMessage                                 message;                                                   

public     :
                     int8                                         get_warning_level() { return(warning_level); }
                     int8                                         get_msg_indent() { return(msg_indent); }
                     ErrorMessage                                &get_message() { return(message); }
public     :         SOSImpExp                                           ErrorProtocol ( );
public     :         SOSImpExp                                           ErrorProtocol (Error &err_obj );
public     :         SOSImpExp                   void SetMessageIndent (uint16 indent=0 );
public     :         SOSImpExp                   void SetWarningLevel (int8 wlevel );
public     :         SOSImpExp                   int8 WarningLevel ( );
public     :         SOSImpExp                   logical Write (const int16 err_code, int8 wlevel, char *errvar1=NULL, char *errvar2=NULL, char *errvar3=NULL, char *errvar4=NULL, char *errvar5=NULL, char *errvar6=NULL );
public     :         SOSImpExp                   logical Write (char *text, int8 wlevel, char *text_type );
};

#endif
