/********************************* Class Source Code ***************************/
/**
\package  VGKbase - 
\class    pc__Project

\brief    


\date     $Date: 2006/07/05 15:32:03,95 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc__Project"

#include  <pVGKbase.h>
#include  <spc__Project.hpp>


/******************************************************************************/
/**
\brief  GetDocumentFolder - 



\return document_folder - Abbruchbedingung

\param  sub_folder - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDocumentFolder"

NString pc__Project :: GetDocumentFolder (char *sub_folder )
{
  NString       document_folder = "";
  char         *szBuffer = NULL;
  if ( Get(FIRST_INSTANCE) )
    document_folder = GPH("document_folder")->GetString();
  if ( document_folder.IsEmpty() )
    if ( szBuffer = GetSysVariable("DocumentFolder") )
      document_folder = szBuffer;  
  
  if ( !document_folder.IsEmpty() && sub_folder )
  {
    document_folder += '/';
    document_folder += sub_folder; 
  }
  return(document_folder);
}

/******************************************************************************/
/**
\brief  GetImportFolder - 



\return string - 

\param  nstring - 
\param  sub_folder - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetImportFolder"

char *pc__Project :: GetImportFolder (NString &nstring, char *sub_folder )
{
  char    *string = NULL;
BEGINSEQ
  nstring = "";

  if ( Get(FIRST_INSTANCE) )
    nstring = GPH("import_folder")->GetString();
  else if ( string = GetSysVariable("ImportFolder") )
    nstring = string;
    
  if ( !nstring.IsEmpty() && sub_folder )
  {
    nstring += '/';
    nstring += sub_folder; 
  }

  if ( !IsDirectory(nstring) )                      ERROR
RECOVER
  nstring = "";
ENDSEQ
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetPOP3 - 



\return value - Abbruchbedingung

\param  attribute_name - 
\param  ini_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPOP3"

NString pc__Project :: GetPOP3 (char *attribute_name, char *ini_name )
{
  PropertyHandle *pop = NULL;
  NString         value = "";
  char*           szBuffer = NULL;
  pop = GPH("pop");
  pop->Get(0);
  value = pop->GetString(attribute_name);
  // INI Opt
  if( value.IsEmpty() )
    if ( szBuffer = GetSysVariable(ini_name) )
      value = szBuffer;
  return(value);
}

/******************************************************************************/
/**
\brief  GetPOP3Address - 



\return mail_address - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPOP3Address"

NString pc__Project :: GetPOP3Address ( )
{

  return GetPOP3("address","MailPOP3Address");

}

/******************************************************************************/
/**
\brief  GetPOP3Password - 



\return mail_password - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPOP3Password"

NString pc__Project :: GetPOP3Password ( )
{

  return GetPOP3("password","MailPOP3Password");


}

/******************************************************************************/
/**
\brief  GetPOP3Port - 



\return mail_port - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPOP3Port"

int16 pc__Project :: GetPOP3Port ( )
{
  int16         mail_port;
  char         *szBuffer = NULL;
  PropertyHandle *pop;
  return 110; // not in structure yet
  pop = GPH("pop");
  pop->Get(0);
  mail_port = pop->GetInt("port");
  // INI Opt
  if( mail_port == 0 )
    if ( szBuffer = GetSysVariable("MailPOP3Port") )
      mail_port = atoi(szBuffer);

  return(mail_port);
}

/******************************************************************************/
/**
\brief  GetPOP3Server - 



\return mail_server - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPOP3Server"

NString pc__Project :: GetPOP3Server ( )
{

  return GetPOP3("host","MailPOP3Host");

}

/******************************************************************************/
/**
\brief  GetPOP3User - 



\return mail_user - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPOP3User"

NString pc__Project :: GetPOP3User ( )
{

  return GetPOP3("user","MailPOP3User");

}

/******************************************************************************/
/**
\brief  GetSMTP - 



\return value - Abbruchbedingung

\param  attribute_name - 
\param  ini_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSMTP"

NString pc__Project :: GetSMTP (char *attribute_name, char *ini_name )
{
  PropertyHandle *pop = NULL;
  NString         value = "";
  char*           szBuffer = NULL;
  pop = GPH("smtp");
  pop->Get(0);
  value = pop->GetString(attribute_name);
  // INI Opt
  if( value.IsEmpty() )
    if ( szBuffer = GetSysVariable(ini_name) )
      value = szBuffer;
  return(value);
}

/******************************************************************************/
/**
\brief  GetSMTPAddress - 



\return mail_address - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSMTPAddress"

NString pc__Project :: GetSMTPAddress ( )
{

  return GetSMTP("address","MailSMTPAddress");

}

/******************************************************************************/
/**
\brief  GetSMTPInfo - 



\return errnum - 

\param  server_string - 
\param  address_string - 
\param  port_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSMTPInfo"

int32 pc__Project :: GetSMTPInfo (NString &server_string, NString &address_string, int16 &port_ref )
{
  DEFLOCALERR
BEGINSEQ
  if ( !Get(FIRST_INSTANCE) )                       ERROR
  
  server_string  = GetSMTPServer();
  address_string = GetSMTPAddress();
  port_ref       = GetSMTPPort();
  
  if ( server_string.IsEmpty() || !port_ref || 
       address_string.IsEmpty()                )    LOCALERR(16)

RECOVER
  if ( !LOCALERROR )
    LOCALERROR = -1;
ENDSEQ
  return(LOCALERROR);
}

/******************************************************************************/
/**
\brief  GetSMTPPassword - 



\return mail_password - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSMTPPassword"

NString pc__Project :: GetSMTPPassword ( )
{

  return GetSMTP("password","MailSMTPPassword");

}

/******************************************************************************/
/**
\brief  GetSMTPPort - 



\return port - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSMTPPort"

int16 pc__Project :: GetSMTPPort ( )
{
  int16         mail_port;
  char         *szBuffer = NULL;
  PropertyHandle *pop;
  return 25; // not in structure yet
  pop = GPH("smtp");
  pop->Get(0);
  mail_port = pop->GetInt("port");
  // INI Opt
  if( mail_port == 0 )
    if ( szBuffer = GetSysVariable("MailSMTPPort") )
      mail_port = atoi(szBuffer);

  return(mail_port);
}

/******************************************************************************/
/**
\brief  GetSMTPServer - 



\return mail_server - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSMTPServer"

NString pc__Project :: GetSMTPServer ( )
{

  return GetSMTP("host","MailSMTPHost");

}

/******************************************************************************/
/**
\brief  GetSMTPUser - 



\return mail_user - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSMTPUser"

NString pc__Project :: GetSMTPUser ( )
{

  return GetSMTP("user","MailSMTPUser");

}

/******************************************************************************/
/**
\brief  pc__Project - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc__Project"

     pc__Project :: pc__Project (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
{



}

/******************************************************************************/
/**
\brief  i01 - 



\param  dbhandle - 
\param  accopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc__Project"

     pc__Project :: pc__Project (DatabaseHandle &dbhandle, PIACC accopt )
                     : PropertyHandle(dbhandle,"_Project",accopt)
{



}


