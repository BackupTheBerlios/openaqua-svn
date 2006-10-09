/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/05|16:41:32,95}|(REF)
\class    ErrorMessage

\brief    


\date     $Date: 2006/04/06 15:08:38,68 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ErrorMessage"

#include  <afxcolli.h>
#include  <pdefault.h>
#include  <sError.hpp>
#include  <sdttm.hpp>
#include  <sErrorMessage.hpp>


/******************************************************************************/
/**
\brief  ErrorMessage


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ErrorMessage"

                        ErrorMessage :: ErrorMessage ( )
                     :   sep00('('),
  sep01('/'),
  sep02('/'),
  sep1(' '),
  sep11(':'),
  sep12(':'),
  sep13(')'),
  sep2(' '),
  sep3('-'),
  sep4(' '),
  sep5(':'),
  sep7('('),
  sep8(')')
{

  SetDateTime();
  memset(component,' ',sizeof(component));
  memset(error_type,' ',sizeof(error_type));
  memset(error_code,' ',sizeof(error_code));
  memset(object_class,' ',sizeof(object_class));
  memcpy(sep6,":: ",3),
  memset(function,' ',sizeof(function));
  memset(text,' ',sizeof(text));
  memcpy(new_line,"\r\n",2);

}

/******************************************************************************/
/**
\brief  SetData

-------------------------------------------------------------------------------
\brief  i0


\param  display_name
\param  message_type
\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetData"

void ErrorMessage :: SetData (char *display_name, char *message_type, char *string )
{

  SetDateTime();

  gvtxstb(component,display_name,sizeof(component));
  gvtxstb(error_type,message_type,sizeof(error_type));
  
  memset(error_code,' ',sizeof(object_class));
  memset(object_class,' ',sizeof(object_class));
  memset(function,' ',sizeof(function));    
  
  gvtxstb(text,string,sizeof(text));
  if ( strlen(string) > sizeof(text) )
    memcpy(text+sizeof(text)-4," ...",4);


}

/******************************************************************************/
/**
\brief  i01


\param  error_obj - Error object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetData"

void ErrorMessage :: SetData (Error *error_obj )
{

  SetDateTime();
  SetError(error_obj);


}

/******************************************************************************/
/**
\brief  SetDateTime


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDateTime"

void ErrorMessage :: SetDateTime ( )
{
  dttm   datentime;  //date'n'time
  uint16 dnthour, dntminute, dntsecond, hsec;
  datentime.SetCurrent();
  
  memcpy(year,"9999",sizeof(year));
  memcpy(month,"99",sizeof(month));
  memcpy(day,"99",sizeof(day));
  memcpy(hour,"99",sizeof(hour));
  memcpy(minute,"99",sizeof(minute));
  memcpy(second,"99",sizeof(second));
  gvtxitp(year,datentime.GetDate().GetYear(),4);
  gvtxitp(month,datentime.GetDate().GetMonth(),2);
  gvtxitp(day,datentime.GetDate().GetDay(),2);
  
  datentime.GetTime().GetHourMinSec(&dnthour,&dntminute,&dntsecond,&hsec);
  gvtxitp(hour,dnthour,2);
  gvtxitp(minute,dntminute,2);
  gvtxitp(second,dntsecond,2);
  
/*
  gvtxitp(year,ctime.GetYear(),4);
  gvtxitp(month,ctime.GetMonth(),2);
  gvtxitp(day,ctime.GetDay(),2);
  gvtxitp(hour,ctime.GetHour(),2);
  gvtxitp(minute,ctime.GetMinute(),2);
  gvtxitp(second,ctime.GetSecond(),2);
*/

}

/******************************************************************************/
/**
\brief  SetError - 



\param  error_obj - Error object
\param  type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetError"

void ErrorMessage :: SetError (Error *error_obj, char *type )
{

  memset(error_code,'9',sizeof(error_code));
  if ( error_obj->CheckError() == USHORTMAX )
    memset(error_code,' ',sizeof(error_code));
  else
    gvtxitp(error_code,error_obj->CheckError(),sizeof(error_code));
  
  if ( !type )
    switch ( error_obj->type )
    {
      case  'M' : type = "Message";                break;
      case  'I' : type = "Info";                   break;
      case  'W' : type = "Warning";                break;
      case  'D' : type = "Decision";               break;
      case  'T' : type = "Fatal Error";            break;
      case  'S' : type = "Status";                 break;
      case  ' ' : type = "";                       break;
      default   : type = "Error";
    }
  gvtxstb(error_type,type,sizeof(error_type));
  
  gvtxstb(component,error_obj->proid,sizeof(component));
  gvtxstb(object_class,error_obj->objid,sizeof(object_class));
  gvtxstb(function,error_obj->modid,sizeof(function));    
  
  gvtxstb(text,error_obj->get_text(),sizeof(text));

}


