/********************************* Class Source Code ***************************/
/**
\package  OPI - 
\class    DBErrorHandle

\brief    Database Error Handle
          The  database error handle provides  extended documentation for errors
          detected  in  the  system.  In  contrast  to the basic ErrorHandle the
          DBErrorHandle  locates  signaled  errors  in the system or application
          database and provides detailled information for the error detected. 
          A  application  specific  error  handle  can  be  defined  and set for
          enabling application specific error handling (-> ErrorHandle).

\date     $Date: 2006/07/16 19:43:48,01 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBErrorHandle"

#include  <pdefault.h>
#include  <chlpmac.h>
#include  <streams.h>
#include  <sACObject.hpp>
#include  <sError.hpp>
#include  <sErrorHandle.hpp>
#include  <sUtilityHandle.hpp>
#include  <sDBErrorHandle.hpp>


/******************************************************************************/
/**
\brief  DBErrorHandle - Constructoe
        The  cnstructor creates an error handle. The object_handle passed to the
        function  should contain the error descriptions  in an extent as defined
        in  the  error(s)  that  are  handled  by  the error handler. For system
        errors  this  is  a  database  object  handle  for  the  system database
        ode.sys.  For  application  errors  the  resource database or dictionary
        should  contain the error definitions. To  activate an error handler for
        the   errors   of   a   certain   error   class   you   can   use   the 
        Error::SetErrorHandle() function.


\param  object_handle - Database Object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBErrorHandle"

     DBErrorHandle :: DBErrorHandle (DBObjectHandle &object_handle )
                     : ErrorHandle (),
  ob_handle(object_handle)
{



}

/******************************************************************************/
/**
\brief  DisplayMessage - Display message
        The  function  displays  a  message  to  the console or in a message box
        (when  GUI-messages are activated). Displaying messages can be supressed
        by  setting the SUPRESS_ERRORS system variable to "YES". Besides writing
        the  message to the  protocol file it  will be displayed on console (for
        console  applications).  This  can  be  supressed  by setting the system
        variable NO_CONSOLE_MESSAGES to "YES".

\return term - Termination code

\param  error_obj - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayMessage"

logical DBErrorHandle :: DisplayMessage (Error *error_obj )
{
  char       errtext[500];
BEGINSEQ
  if ( TestSysVariable("SUPRESS_ERRORS","YES") )     LEAVESEQ

  ILock();
  if ( error_obj->CheckError() )
    message.SetError(error_obj);
    
  ErrorHandle::DisplayMessage(error_obj);  
    
  IUnlock();

RECOVER

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  GetError - Get error text from resource database
        The  function provides the  error text stored  in the resource data base
        passed  as error_source or set as error_source in the error object. This
        is  usually  the  application  resource database that contains the error
        defintions  in  an  extent  with  the name of the error class. The error
        text  will  be  provided  according  to  the  language  set in the error
        handle. 
        When  the error is not found  a message "Undefined error" containing the
        error  variables set is created. The  function returns the error type as
        set in the error defintion.

\return err_type - 

\param  error_obj - 
\param  error_source - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetError"

char DBErrorHandle :: GetError (Error *error_obj, void *error_source )
{
  DBObjectHdl     obhandle;
  Error           saveerr  = *error_obj;
  Error          *erro     = error_obj;
  PropertyHandle *descr_pi = NULL;
  char           *errtext  = NULL;
  char            type     = 'E';
  int32           errcode  = 0;
  char            string[ID_SIZE+1];
BEGINSEQ
//ILock();  klemmt, wenn dictionary ein Fehler ausgeben will
  error_obj->stsslck();
  errcode = error_obj->CheckError();
  if ( !errcode )                                    LEAVESEQ
  error_obj->Reset();

  switch ( errcode )
  {
    case 100  : errtext = "Database could not be closed, not opened.";   LEAVESEQ
    case 400  : errtext = "Open Dictionary: Error in generation phase."; LEAVESEQ
    default   : ;
  }

  if ( error_source )
    obhandle = *(DBObjectHandle *)error_source;
  else if ( error_obj->get_error_srce() ) 
    obhandle = *(DBObjectHandle *)error_obj->get_error_srce();
  else
    obhandle = ob_handle;
  if ( !obhandle                                                 && 
       !(sdbuptr && (obhandle = sdbuptr->sdbusys->object_handle).IsOpened() ))
                                                     ERROR
  
  if ( errcode > META_ERROR_BASE )   // meta error (l:\opi2\h\csdberr.h)
  {
    if ( errcode == SERVER_ERROR )
    {
      type = error_obj->type;                        LEAVESEQ
    }

    if ( erro = &GetErrorObject((ProcessVariableNames)(errcode-META_ERROR_BASE)) )
    {
// text sollte schon aufgelöst sein
//    type = GetError(erro,erro->get_error_srce());  
      saveerr.type = erro->type;
      type         = erro->type;
      errtext      = strcpy(saveerr.get_text(),erro->get_text());
      strcpy(saveerr.get_err_var1(),erro->get_err_var1());
      strcpy(saveerr.get_err_var2(),erro->get_err_var2());
      strcpy(saveerr.get_err_var3(),erro->get_err_var3());
      strcpy(saveerr.get_err_var4(),erro->get_err_var4());
      strcpy(saveerr.get_err_var5(),erro->get_err_var5());
      strcpy(saveerr.get_err_var6(),erro->get_err_var6());
      LEAVESEQ
    }
    erro = error_obj;
    ERROR
  }
  
  errcode = saveerr.CheckError();
  {
    PropertyHandle  ec_ph(obhandle,"ODC_ErrorClass",PI_Read); SDBCERR
    PropertyHandle phsaveerrerr_class(saveerr.err_class);
    if ( ec_ph.Get(phsaveerrerr_class) )
    {
      PropertyHandle errpi(&ec_ph,"errors");         SDBCERR
      if ( errpi((char *)&errcode) )    
      {
        type = *errpi.GetPropertyHandle("_errtyp")->GetString(); 
        if ( (descr_pi = errpi.GPH("resource_ref")) && descr_pi->Get(0) &&
             (descr_pi = descr_pi->GPH("description")) && descr_pi->Get(0) )
        {
          errtext = descr_pi->GetText("definition.name");
          errtext = gvtxbts(saveerr.get_text(),errtext,80);
        }
      }
    } 
    if ( errtext )                                   LEAVESEQ
  }
  
  if ( !sdbuptr )                                    ERROR
  obhandle = sdbuptr->sdbusys->object_handle;
  obhandle->PushConnectionResult();
  if ( obhandle.GetStructDef(saveerr.err_class) )
  {
    PropertyHandle  ec_ph(obhandle,"ODC_ErrorClass",PI_Read);
    PropertyHandle  errcls_ident(saveerr.err_class);
    if ( ec_ph.Get(errcls_ident) )
    {
      PropertyHandle errpi(&ec_ph,"errors");         
      if ( errpi((char *)&errcode) )
      {
        type = *errpi.GetPropertyHandle("_errtyp")->GetString(); 
        if ( (descr_pi = errpi.GPH("resource_ref")) && descr_pi->Get(0) &&
             (descr_pi = descr_pi->GPH("description")) && descr_pi->Get(0) )
        {
          errtext = descr_pi->GetString("definition.name");
          errtext = gvtxbts(saveerr.get_text(),errtext,80);
        }
      }
    }
  }
  obhandle->PopConnectionResult();

RECOVER
  saveerr.type = UNDEF;
  type = UNDEF;
ENDSEQ
  *error_obj = saveerr;
//IUnlock();
  return (type);

}

/******************************************************************************/
/**
\brief  GetErrorHelpID - Get context help id for the error
        The  function returns a context  help id for the  error that can be used
        to  call the online help for errors, that can be created using the ODABA
        design  tools or by any other  application. By default the error context
        id is the resource id of the error definition.

\return helpid - 

\param  error_obj - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetErrorHelpID"

int32 DBErrorHandle :: GetErrorHelpID (Error *error_obj )
{
  ik_HelpTopic  idkey;
  DBObjectHdl   obhandle;
  int32          helpid = HELP_INDEX;
BEGINSEQ
//ILock();  klemmt, wenn dictionary ein Fehler ausgeben will
//  if ( !(obhandle = *(DBObjectHdl *)error_obj->get_error_srce()) && 
//       !(obhandle = ob_handle)                                   && 
//       !(sdbuptr && (obhandle = sdbuptr->sdbusys.object_handle).IsOpened()))
  if ( error_obj->get_error_srce() ) 
    obhandle = *(DBObjectHdl *)error_obj->get_error_srce();
  else
    obhandle = ob_handle;
  if ( !obhandle                                                 && 
       !(sdbuptr && (obhandle = sdbuptr->sdbusys->object_handle).IsOpened() ))
                                                     ERROR
/*
  PI(mem)     ht_pi(obhandle,"HelpTopic",PI_Read); SDBCERR
  if ( ht_pi.SetOrder("ik_HelpTopic") )              ERROR
  
//  idkey.topic_type = HT_Error;  // geht nich zu übersetzen 18.8.98
  idkey.ext_number = error_obj->CheckError();
  gvtxstb(idkey.name1,error_obj->objid,ID_SIZE);
  memset(idkey.name2,' ',ID_SIZE);

  if ( !ht_pi((char *)&idkey) )                      ERROR
  if ( !(helpid = ht_pi.GetPropertyHandle("#_AUTOIDENT")->GetInt()) )
    helpid = HELP_INDEX;
*/
RECOVER

ENDSEQ
//IUnlock();
  return(helpid);
}

/******************************************************************************/
/**
\brief  GetObjectHandle - Get resource object handle
        The  function returns  the database  object handle  for the error handle
        that has been set for error look up.

\return obhandle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetObjectHandle"

DBObjectHandle &DBErrorHandle :: GetObjectHandle ( )
{

  return(ob_handle);

}

/******************************************************************************/
/**
\brief  SetObjectHandle - Set resource object handle
        The  function sets the database object  handle for the error handle that
        is used for error look up.


\param  obhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetObjectHandle"

void DBErrorHandle :: SetObjectHandle (DBObjectHandle &obhandle )
{

  ob_handle = obhandle;

}

/******************************************************************************/
/**
\brief  ~DBErrorHandle - Destructor
        The function destroys the error handle.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBErrorHandle"

     DBErrorHandle :: ~DBErrorHandle ( )
{



}


