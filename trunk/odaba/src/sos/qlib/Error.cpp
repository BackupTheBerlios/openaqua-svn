/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    Error

\brief    General Error object
          The  error object is  used to store  and pass error information to the
          application.  Errors are identified by error class and eror number. In
          addition  the  class  and  function  name  detecting the problem and a
          short  error  explanation  can  be  provided.  Moreover,  an error may
          include  upto  6  context  depending  error  variables  that  can  be 
          displayed in the error message. 
          Usually  error messages are written to a log file (error.lst) which is
          stored  in  a  folder  addressed  by the TRACE environment or ini-file
          variable.  It  is,  however,  also  possible  to display errors on the
          terminal. 
          Usually  errors should  be reset  in all  functions that may signal an
          error.  Otherwise the  calling function  may not  be able to determine
          whether  the error signaled is an old  error or has just been signaled
          in  the called  function. This  strategy requires,  on the other hand,
          that  signaled errors have to be saved when other functions are called
          in  the error handling  thet might generate  errors again, since those
          functions  will reset  the error.  You can  use the Copy() function to
          save the error. 
          The  way errors are presented in  the application depends on the error
          handler  installed (ErroerHandle).  Usually errors  are written to the
          console  output for  console applications  and shown  in a message box
          for windows applications.

\date     $Date: 2006/08/27 14:26:07,45 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "Error"

#include  <fileacc.h>
#include  <pdefault.h>
#include  <streams.h>
#include  <sCTX_Base.hpp>
#include  <sErrorHandle.hpp>
#include  <sRessourceLock.hpp>
#include  <sThreadEntry.hpp>
#include  <strc.hpp>
#include  <strcc.hpp>
#include  <sError.hpp>


/******************************************************************************/
/**
\brief  CheckError - 



\return rc - Retrun code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckError"

int32 Error :: CheckError ( )
{

  return ( this ? error : UNDEF);

}

/******************************************************************************/
/**
\brief  Copy - Copy error

        The   function   copies   the   error   object   to  save relevant error
        information.  You can  use the  function to  save error information that
        might be destroyed when calling other functions.


\param  err_obj - Error object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

void Error :: Copy (Error &err_obj )
{

  *(sts *)this = (sts)err_obj;
  error = err_obj.error;
  memcpy(modid,err_obj.modid,sizeof(modid));
  memcpy(objid,err_obj.objid,sizeof(objid));
  memcpy(proid,err_obj.proid,sizeof(proid));
  memcpy(err_class,err_obj.err_class,sizeof(err_class));
  memcpy(title,err_obj.title,sizeof(title));
  tdspl = err_obj.tdspl;
  tlist = err_obj.tlist;
  thier = err_obj.thier;
  memcpy(err_var1,err_obj.err_var1,sizeof(err_var1));
  memcpy(err_var2,err_obj.err_var2,sizeof(err_var2));
  memcpy(err_var3,err_obj.err_var3,sizeof(err_var3));
  memcpy(err_var4,err_obj.err_var4,sizeof(err_var4));
  memcpy(err_var5,err_obj.err_var5,sizeof(err_var5));
  memcpy(err_var6,err_obj.err_var6,sizeof(err_var6));
  type = err_obj.type;
  memcpy(text,err_obj.text,sizeof(text));


}

/******************************************************************************/
/**
\brief  CreateExceptions - 




\param  exceptions - Trow exception
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateExceptions"

void Error :: CreateExceptions (logical exceptions )
{

  throw_exception = exceptions;


}

/******************************************************************************/
/**
\brief  DisplayMessage - Dispaly message

        The  function allows displaying a message for a signaled or passed error
        code.  Depending  on  the  error  heandle set for the error the error is
        written to the console or displayed on the terminal.

\return term - Success
-------------------------------------------------------------------------------
\brief  i0 - Display user error

        The  function  displays  an  error  passed by the user. The passed error
        variables  are  inserted  for  the  place  holders  in the error message
        definition.  When  the  error  code  passed is 0 the last signaled error
        code is used instead.

\param  err_code - Error code
\param  errvar1 - First error variable
\param  errvar2 - Second error variable
\param  errvar3 - Third error variable
\param  errvar4 - Fourth error variable
\param  errvar5 - Fifth error variable
\param  errvar6 - Sixth error variable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayMessage"

logical Error :: DisplayMessage (const int16 err_code, char *errvar1, char *errvar2, char *errvar3, char *errvar4, char *errvar5, char *errvar6 )
{

  return(DisplayMessage(error_srce,err_code,errvar1,errvar2,errvar3,errvar4,errvar5,errvar6));

}

/******************************************************************************/
/**
\brief  i1 - Display current error

        Usually  error  messages  are  written  to  the  error  log,  only. This
        function  shows the error  in the given  application context (console or
        message box).

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayMessage"

logical Error :: DisplayMessage ( )
{

  return( DisplayMessage(error_srce) );

}

/******************************************************************************/
/**
\brief  i2 - Display application error with defined error database

        The  function  displays  an  error  passed by the user. The passed error
        variables  are  inserted  for  the  place  holders  in the error message
        definition.  When  the  error  code  passed is 0 the last signaled error
        code  is used instead. The function retrieves the error message from the
        error  source (usually  an error  database) passed  to the error calling
        the ErrorHandle::GetError() function.

\param  error_source - Handle for the error source
\param  err_code - Error code
\param  errvar1 - First error variable
\param  errvar2 - Second error variable
\param  errvar3 - Third error variable
\param  errvar4 - Fourth error variable
\param  errvar5 - Fifth error variable
\param  errvar6 - Sixth error variable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayMessage"

logical Error :: DisplayMessage (void *error_source, const int16 err_code, char *errvar1, char *errvar2, char *errvar3, char *errvar4, char *errvar5, char *errvar6 )
{

  if ( errvar1 )
    SetErrorVariable(1,errvar1);
  if ( errvar2 )
    SetErrorVariable(2,errvar2);
  if ( errvar3 )
    SetErrorVariable(3,errvar3);
  if ( errvar4 )
    SetErrorVariable(4,errvar4);
  if ( errvar5 )
    SetErrorVariable(5,errvar5);
  if ( errvar6 )
    SetErrorVariable(6,errvar6);

  if ( err_code )
    SetError(err_code,NULL,NULL);
  return( DisplayMessage(error_source) );

}

/******************************************************************************/
/**
\brief  i3 - 

        The  function retrieves the error message from the error source (usually
        an    error    database)    passed    to    the    error    calling  the
        ErrorHandle::GetError()  function  and  displays  the  message  in  the 
        application  context. The way the error  message is displayed depends on
        the   ErrorHandle::DisplayMessage()   function   of   the   error handle
        associated with the error.

\param  error_source - Handle for the error source
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayMessage"

logical Error :: DisplayMessage (void *error_source )
{
  static      RessourceLock   res_lock(NO);
  int32       loc_err = CheckError();
  logical     term = NO;
BEGINSEQ
  res_lock.ILock();

//  if ( !error || error >= 1000 )                     LEAVESEQ 18.8.99
  if ( !loc_err || loc_err == 1000 )                   LEAVESEQ
  

  SetupErrText(error_source);
  
  if ( error_handle )
    term = error_handle->DisplayMessage(this);
//  else
//    term = ErrorHandle().DisplayMessage(this); (geht immer auf Console)
  
  

ENDSEQ
  ResetAllErrors();
  res_lock.IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  Error - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  metacode - Meta code for the error
\param  pid - Project name
\param  errclass - Error class
\param  ttext - Error title
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Error"

     Error :: Error (int16 metacode, char *pid, char *errclass, char *ttext )
                     : sts (),
  error(0),
  tdspl(NO),
  tlist(NO),
  thier(NO),
  meta_error(metacode),
  error_handle(NULL),
  error_srce(NULL),
  throw_exception(NO)
{

  Initialize(metacode,pid,errclass,ttext);

}

/******************************************************************************/
/**
\brief  i1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Error"

     Error :: Error ( )
                     : sts (),
  error(0),
  tdspl(NO),
  tlist(NO),
  thier(NO),
  meta_error(UNDEF),
  error_handle(NULL),
  error_srce(NULL),
  throw_exception(NO)
{

  Initialize();
  ResetError();
  
  *proid     = 0;
  *err_class = 0;
  *title     = 0;


}

/******************************************************************************/
/**
\brief  i2 - 



\param  err_obj - Error object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Error"

     Error :: Error (Error &err_obj )
{

  *this = err_obj;


}

/******************************************************************************/
/**
\brief  GetDecision - Ask for user decision

        The  function  creates  an  message  from  the error code and the passed
        error  variables  and  generates  a  decision  that  is displayed in the
        specific  application context (console  message for console applications
        and  decision  box  for  windows  applications.  To execute the function
        successfully  an  error  handle  should  be  set. If not, a simple error
        handle will be constructed.

\return term - Success
-------------------------------------------------------------------------------
\brief  i0 - Display application decision

        The  function displays a decision forced  by the application. The passed
        error  variables are inserted for the place holders in the error message
        definition.  The decision  text is  taken from  the eror description for
        the  passed error code as defined in the error source set for the active
        arror handle.

\param  err_code - Error code
\param  errvar1 - First error variable
\param  errvar2 - Second error variable
\param  errvar3 - Third error variable
\param  errvar4 - Fourth error variable
\param  errvar5 - Fifth error variable
\param  errvar6 - Sixth error variable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDecision"

logical Error :: GetDecision (const int16 err_code, char *errvar1, char *errvar2, char *errvar3, char *errvar4, char *errvar5, char *errvar6 )
{

  return(GetDecision(error_srce,err_code,errvar1,errvar2,errvar3,errvar4,errvar5,errvar6));

}

/******************************************************************************/
/**
\brief  i1 - Display predefined decision

        The  function displays  a decision  with the  error text set in the text
        field  of  the  error  object.  This  function shows the decision in the
        given application context (console or message box).

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDecision"

logical Error :: GetDecision ( )
{

  *text = 0;
  return( GetDecision(error_srce) );

}

/******************************************************************************/
/**
\brief  i2 - Display application decision with different error source

        The  function  displays  a  decision  forced  by  the  application.  The
        decision  text is  constructed from  the error  definition read from the
        passed  error  source  replacing  the  place holders by the passed error
        variables.

\param  error_source - Handle for the error source
\param  err_code - Error code
\param  errvar1 - First error variable
\param  errvar2 - Second error variable
\param  errvar3 - Third error variable
\param  errvar4 - Fourth error variable
\param  errvar5 - Fifth error variable
\param  errvar6 - Sixth error variable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDecision"

logical Error :: GetDecision (void *error_source, const int16 err_code, char *errvar1, char *errvar2, char *errvar3, char *errvar4, char *errvar5, char *errvar6 )
{
  int16               errcd = err_code;
  if ( errvar1 )
    SetErrorVariable(1,errvar1);
  if ( errvar2 )
    SetErrorVariable(2,errvar2);
  if ( errvar3 )
    SetErrorVariable(3,errvar3);
  if ( errvar4 )
    SetErrorVariable(4,errvar4);
  if ( errvar5 )
    SetErrorVariable(5,errvar5);
  if ( errvar6 )
    SetErrorVariable(6,errvar6);

  if ( !errcd )
    errcd = USHORTMAX;
  SetError(errcd,NULL,NULL);
    
  return( GetDecision(error_source) );

}

/******************************************************************************/
/**
\brief  i3 - Display decision with different error source

        The  function  displays  a  decision  forced  by  the  application.  The
        decision  text is  constructed from  the error  definition read from the
        passed  error source replacing the place  holders by the error variables
        set in the error (err_var1... 6).

\param  error_source - Handle for the error source
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDecision"

logical Error :: GetDecision (void *error_source )
{
  static      RessourceLock   res_lock(NO);
  int32       loc_err = CheckError();
  logical     term = NO;
BEGINSEQ
  res_lock.ILock();

//  if ( !error || error >= 1000 )                     LEAVESEQ 18.8.99
  SetupErrText(error_source);
  
  if ( error_handle )
    term = error_handle->GetDecision(this);
  else
    ErrorHandle().GetDecision(this);
  

ENDSEQ
  ResetAllErrors();
  res_lock.IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  GetErrorHelpID - 



\return helpid - Context help id

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetErrorHelpID"

int32 Error :: GetErrorHelpID ( )
{

  return(error_handle ? error_handle->GetErrorHelpID(this) : UNDEF);

}

/******************************************************************************/
/**
\brief  GetErrorText - 



\return err_text - Error text

\param  error_source - Handle for the error source
\param  err_code - Error code
\param  errvar1 - First error variable
\param  errvar2 - Second error variable
\param  errvar3 - Third error variable
\param  errvar4 - Fourth error variable
\param  errvar5 - Fifth error variable
\param  errvar6 - Sixth error variable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetErrorText"

char *Error :: GetErrorText (void *error_source, const int16 err_code, char *errvar1, char *errvar2, char *errvar3, char *errvar4, char *errvar5, char *errvar6 )
{
  static     RessourceLock   res_lock(NO);
  DWORD      threadid = ThreadEntry::GetThreadID();

BEGINSEQ
  if ( !err_code && thread_id != threadid )             LEAVESEQ
  
  res_lock.ILock();
  
  if ( errvar1 )
    SetErrorVariable(1,errvar1);
  if ( errvar2 )
    SetErrorVariable(2,errvar2);
  if ( errvar3 )
    SetErrorVariable(3,errvar3);
  if ( errvar4 )
    SetErrorVariable(4,errvar4);
  if ( errvar5 )
    SetErrorVariable(5,errvar5);
  if ( errvar6 )
    SetErrorVariable(6,errvar6);

  if ( err_code )
    SetError(err_code,NULL,NULL);

  SetupErrText(error_source);
  
  ResetError();
  
  res_lock.IUnlock();

ENDSEQ
  return(text);
}

/******************************************************************************/
/**
\brief  GetErrorVariable - 



\return vartext - Variable text

\param  varnum - Variable number
\param  inittext - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetErrorVariable"

char *Error :: GetErrorVariable (int8 varnum, char *inittext )
{
  char      *ervstr = NULL;
BEGINSEQ
  if ( !this )                                      ERROR

  switch ( varnum )
  {
    case 1  : ervstr = err_var1;                    break;  
    case 2  : ervstr = err_var2;                    break;  
    case 3  : ervstr = err_var3;                    break;  
    case 4  : ervstr = err_var4;                    break;  
    case 5  : ervstr = err_var5;                    break;  
    case 6  : ervstr = err_var6;                    break;  
    default : ERROR
  }
    

RECOVER
  ervstr = inittext;
ENDSEQ
  return(ervstr);
}

/******************************************************************************/
/**
\brief  GetHandle - 



\return error_hdl - Error handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHandle"

ErrorHandle *Error :: GetHandle ( )
{

  return ( this ? error_handle : NULL );

}

/******************************************************************************/
/**
\brief  GetText - 



\return text - Error text

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetText"

char *Error :: GetText ( )
{
 

  return(text);

}

/******************************************************************************/
/**
\brief  GetTitle - 



\return ttext - Error title

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTitle"

char *Error :: GetTitle ( )
{

  return(title);

}

/******************************************************************************/
/**
\brief  Initialize - Initialize error

        The function initializes an error object.

-------------------------------------------------------------------------------
\brief  i0 - Reset error object

        The  function  will  reset  all  attributes  in the error objects to its
        initial values.

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void Error :: Initialize ( )
{

  *text     = 0;
  
  *err_var1 = 0;
  *err_var2 = 0;
  *err_var3 = 0;  
  *err_var4 = 0;  
  *err_var5 = 0;
  *err_var6 = 0;
  
  type      = ' ';
  thread_id = 0;


}

/******************************************************************************/
/**
\brief  i01 - Initialize error object

        The  function  wil  reset  the  orror  specification with the parameters
        passed.

\param  metacode - Meta code for the error
\param  pid - Project name
\param  errclass - Error class
\param  ttext - Error title
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void Error :: Initialize (int16 metacode, char *pid, char *errclass, char *ttext )
{

  error           = 0;
  tdspl           = NO;
  tlist           = NO;
  thier           = NO;
  meta_error      = metacode;
  error_handle    = NULL;
  error_srce      = NULL;
  throw_exception = NO;  
  
  Initialize();
  ResetError();
  
  if ( errclass )
    gvtxbts(err_class,errclass,sizeof(err_class));
  
  if ( pid )
    strncpy(proid,pid,sizeof(proid));

  if ( ttext )
    strncpy(title,ttext,sizeof(title));

}

/******************************************************************************/
/**
\brief  InsertStatField - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertStatField"

void Error :: InsertStatField ( )
{

  if ( error_handle )
    error_handle->InsertStatField();

}

/******************************************************************************/
/**
\brief  IsGUIApplication - 



\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsGUIApplication"

logical Error :: IsGUIApplication ( )
{

  return( error_handle ? error_handle->get_gui_message() : NO);

}

/******************************************************************************/
/**
\brief  OutputMessage - 




\param  display_name - 
\param  message_type - 
\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OutputMessage"

void Error :: OutputMessage (char *display_name, char *message_type, char *string )
{


  if ( error_handle )
    error_handle->OutputMessage(display_name,message_type,string);



}

/******************************************************************************/
/**
\brief  RemoveStatField - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveStatField"

void Error :: RemoveStatField ( )
{

  if ( error_handle )
    error_handle->RemoveStatField();

}

/******************************************************************************/
/**
\brief  Reset - Reset error text

        The  function  resets  the  error  text  and the error type, but not the
        error code. For resetting the error object call ResetError().


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void Error :: Reset ( )
{

  if ( this )
  {
    *text = 0;

    type    = error > 0          ? 'E'  : 
              error == USHORTMAX ? '*'  :
              error > -300       ? 'I'  :
              error > -600       ? 'S'  : 
                                   ' ';
  }


}

/******************************************************************************/
/**
\brief  ResetAllErrors - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetAllErrors"

void Error :: ResetAllErrors ( )
{

  if ( this && error_handle )
    error_handle->ResetAllErrors();

}

/******************************************************************************/
/**
\brief  ResetError - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetError"

void Error :: ResetError ( )
{

  if ( this )
  {
    error      = 0;
    *objid     = 0;
    *modid     = 0;
    thread_id  = 0;
  }

}

/******************************************************************************/
/**
\brief  ResetErrorVariables - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetErrorVariables"

void Error :: ResetErrorVariables ( )
{
  char     *ervstr;
  *err_var1 = 0;
  *err_var2 = 0;
  *err_var3 = 0;
  *err_var4 = 0;
  *err_var5 = 0;
  *err_var6 = 0;


}

/******************************************************************************/
/**
\brief  SetError - Signal error

        The  function signals an  error for the  error object. Usually the error
        is recorded in a log file (error.lst).


\param  err_code - Error code
\param  obj - Object or class name
\param  mod - Module or function
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetError"

void Error :: SetError (const int16 err_code, char *obj, char *mod )
{

BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( !err_code )
    ResetError();
  else
  {
    if ( obj && *obj )
      strncpy(objid,obj,sizeof(objid)-1);
  
    if ( mod && *mod )
      strncpy(modid,mod,sizeof(modid)-1);

    error = err_code == AUTO ? USHORTMAX : err_code;

    if ( obj && mod )
      WriteError();
  }
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetErrorVariable - 




\param  varnum - Variable number
\param  vartext - Variable text
\param  varlen - Variable length
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetErrorVariable"

void Error :: SetErrorVariable (int8 varnum, char *vartext, int16 varlen )
{
  char     *ervstr = NULL;
BEGINSEQ
  if ( ervstr = GetErrorVariable(varnum,NULL) )
  {
    strcpy(ervstr,"");
    if ( vartext )
    {
      if ( !varlen )
        varlen = strlen(vartext);
      gvtxbts(ervstr,vartext,MIN(ERROR_VARLEN,varlen));
      if ( varlen > ERROR_VARLEN )
        memset(ervstr+ERROR_VARLEN-3,'.',3);
    }
  }

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetErrorVariables - 




\param  max_len - maximum text length
\param  errvar1 - First error variable
\param  errvar2 - Second error variable
\param  errvar3 - Third error variable
\param  errvar4 - Fourth error variable
\param  errvar5 - Fifth error variable
\param  errvar6 - Sixth error variable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetErrorVariables"

void Error :: SetErrorVariables (int32 max_len, char *errvar1, char *errvar2, char *errvar3, char *errvar4, char *errvar5, char *errvar6 )
{

  if ( this )
  {
    if ( errvar1 )
      SetErrorVariable(1,errvar1,max_len);
    if ( errvar2 )
      SetErrorVariable(2,errvar2,max_len);
    if ( errvar3 )
      SetErrorVariable(3,errvar3,max_len);
    if ( errvar4 )
      SetErrorVariable(4,errvar4,max_len);
    if ( errvar5 )
      SetErrorVariable(5,errvar5,max_len);
    if ( errvar6 )
      SetErrorVariable(6,errvar6,max_len);
  }

}

/******************************************************************************/
/**
\brief  SetErrorWithVariables - 




\param  err_code - Error code
\param  obj - Object or class name
\param  mod - Module or function
\param  errvar1 - First error variable
\param  errvar2 - Second error variable
\param  errvar3 - Third error variable
\param  errvar4 - Fourth error variable
\param  errvar5 - Fifth error variable
\param  errvar6 - Sixth error variable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetErrorWithVariables"

void Error :: SetErrorWithVariables (const int16 err_code, char *obj, char *mod, char *errvar1, char *errvar2, char *errvar3, char *errvar4, char *errvar5, char *errvar6 )
{

  SetErrorVariables(UNDEF,errvar1,errvar2,errvar3,errvar4,errvar5,errvar6);
  SetError(err_code,obj,mod);


}

/******************************************************************************/
/**
\brief  SetHandle - 




\param  error_hdl - Error handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetHandle"

void Error :: SetHandle (ErrorHandle *error_hdl )
{

BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( error_hdl )
  {
    if ( error_handle )
      SetHandle(NULL);
    error_handle = error_hdl;
    error_handle->AddError(this);
  }
  else
  {
    if ( error_handle )
      error_handle->RemoveError(this);
    error_handle = NULL;
  }



RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetLanguage - 




\param  err_lang - Error language
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLanguage"

void Error :: SetLanguage (char *err_lang )
{

  if ( error_handle )
    error_handle->SetLanguage(err_lang);

}

/******************************************************************************/
/**
\brief  SetSource - 




\param  error_source - Handle for the error source
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSource"

void Error :: SetSource (void *error_source )
{

  error_srce = error_source;

}

/******************************************************************************/
/**
\brief  SetStatField - 




\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetStatField"

void Error :: SetStatField (char *string )
{

  if ( error_handle )
    error_handle->SetStatField(string);

}

/******************************************************************************/
/**
\brief  SetStatText - 




\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetStatText"

void Error :: SetStatText (char *string )
{

  if ( error_handle )
    error_handle->SetStatText(string);

}

/******************************************************************************/
/**
\brief  SetText - 




\param  err_text - Error text
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetText"

void Error :: SetText (char *err_text )
{

  memset(text,0,sizeof(text));
  strncpy(text,err_text,sizeof(text)-1);

}

/******************************************************************************/
/**
\brief  SetTitle - 




\param  ttext - Error title
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTitle"

void Error :: SetTitle (char *ttext )
{

  memset(title,0,sizeof(title));
  strncpy(title,ttext,sizeof(title)-1);

}

/******************************************************************************/
/**
\brief  SetTracePath - 




\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTracePath"

void Error :: SetTracePath (char *cpath )
{

  if ( error_handle )
    error_handle->SetTracePath(cpath);
  else
    SetSysVariable("TRACE",cpath);

}

/******************************************************************************/
/**
\brief  SetType - Set eror type

        The  function sets the passed error type. The error type is evaluated by
        the  associated  error  handle  for  displaying  error  messages  in  an
        appropriate way.


\param  err_type - Error type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetType"

void Error :: SetType (char err_type )
{

  type = err_type;

}

/******************************************************************************/
/**
\brief  SetupErrText - 




\param  error_source - Handle for the error source
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupErrText"

void Error :: SetupErrText (void *error_source )
{
  char       area[ERROR_TEXTL+1];
BEGINSEQ
  if (!error )                                       LEAVESEQ
  if ( error_handle && error_handle->SetBusy(YES) )  LEAVESEQ
  
  *text = 0;
  if ( error == USHORTMAX )
  {
    strcpy(text,"%s %s %s %s %s %s");
    type  = ' ';
  }
  else if ( !error_handle || !(type = error_handle->GetError(this,error_source)) )
    type  = ' ';

  error_handle->SetBusy(NO);  
  if ( *text )
  {  
    strncpy(area,text,ERROR_TEXTL);
    gvtsexc(area,"\\n","\n",ERROR_TEXTL);
    
    gvtsexc(area,"%1",err_var1,ERROR_TEXTL+1);
    gvtsexc(area,"%2",err_var2,ERROR_TEXTL+1);
    gvtsexc(area,"%3",err_var3,ERROR_TEXTL+1);
    gvtsexc(area,"%4",err_var4,ERROR_TEXTL+1);
    gvtsexc(area,"%5",err_var5,ERROR_TEXTL+1);
    gvtsexc(area,"%6",err_var6,ERROR_TEXTL+1);
    sprintf(text,area,err_var1,err_var2,err_var3,err_var4,err_var5,err_var6);
  }
  else
  {
    if ( type <= ' ' )
      type = 'E';
    sprintf(text,"Undescribed Error : %d in %s::%s (%s,%s,%s,%s,%s,%s)",
            error,objid,modid,err_var1,err_var2,err_var3,err_var4,err_var5,err_var6);
  }

RECOVER

ENDSEQ


}

/******************************************************************************/
/**
\brief  ShowMessage - 



\return term - Success
-------------------------------------------------------------------------------
\brief  i0 - 



\param  err_code - Error code
\param  errvar1 - First error variable
\param  errvar2 - Second error variable
\param  errvar3 - Third error variable
\param  errvar4 - Fourth error variable
\param  errvar5 - Fifth error variable
\param  errvar6 - Sixth error variable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowMessage"

logical Error :: ShowMessage (const int16 err_code, char *errvar1, char *errvar2, char *errvar3, char *errvar4, char *errvar5, char *errvar6 )
{

  return(ShowMessage(error_srce,err_code,errvar1,errvar2,errvar3,errvar4,errvar5,errvar6));

}

/******************************************************************************/
/**
\brief  i1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowMessage"

logical Error :: ShowMessage ( )
{

  return( ShowMessage(error_srce) );

}

/******************************************************************************/
/**
\brief  i2 - 



\param  error_source - Handle for the error source
\param  err_code - Error code
\param  errvar1 - First error variable
\param  errvar2 - Second error variable
\param  errvar3 - Third error variable
\param  errvar4 - Fourth error variable
\param  errvar5 - Fifth error variable
\param  errvar6 - Sixth error variable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowMessage"

logical Error :: ShowMessage (void *error_source, const int16 err_code, char *errvar1, char *errvar2, char *errvar3, char *errvar4, char *errvar5, char *errvar6 )
{

  if ( errvar1 )
    SetErrorVariable(1,errvar1);
  if ( errvar2 )
    SetErrorVariable(2,errvar2);
  if ( errvar3 )
    SetErrorVariable(3,errvar3);
  if ( errvar4 )
    SetErrorVariable(4,errvar4);
  if ( errvar5 )
    SetErrorVariable(5,errvar5);
  if ( errvar6 )
    SetErrorVariable(6,errvar6);

  if ( err_code )
    SetError(err_code,NULL,NULL);
  return( ShowMessage(error_source) );

}

/******************************************************************************/
/**
\brief  i3 - 



\param  error_source - Handle for the error source
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowMessage"

logical Error :: ShowMessage (void *error_source )
{
  static      RessourceLock   res_lock(NO);
  int32       loc_err = CheckError();
  logical     term = NO;
BEGINSEQ
  res_lock.ILock();

//  if ( !error || error >= 1000 )                     LEAVESEQ 18.8.99
  if ( !loc_err || loc_err == 1000 )                   LEAVESEQ
  

  SetupErrText(error_source);
  
  if ( error_handle )
    term = error_handle->ShowMessage(this);
  
  

ENDSEQ
  ResetAllErrors();
  res_lock.IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  SystemCheck - 



\return term - Success

\param  cond - Return value
\param  obj - Object or class name
\param  mod - Module or function
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SystemCheck"

logical Error :: SystemCheck (logical cond, char *obj, char *mod )
{
  logical                 term = NO;
  if ( cond )
  {
    SetError(99,obj,mod);
    ResetError();
  }  


  return(cond);

}

/******************************************************************************/
/**
\brief  TraceFunction - 




\param  tptr - 
\param  mod - Module or function
\param  obj - Object or class name
\param  phase - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TraceFunction"

void Error :: TraceFunction (void **tptr, char *mod, char *obj, char phase )
{
  trcc     *trccptr;
  trc     **trcptr = (trc **)tptr; 
  char      string[256];
  char      msg[80]; 

  if ( !trcptr )
  {
    if ( trccptr = (trcc *)GetProcessVariable(PVN_SOSTraceObject) )
      *trcptr = trccptr->trccloc(trcptr,obj,mod);
  }
  
  if ( *trcptr && tlist )
    switch ( phase )
    {
      case 'B' : (*trcptr)->trcbeg(obj,mod);        break;   
      case 'R' : (*trcptr)->trcrec(obj,mod);        break;   
      case 'E' : (*trcptr)->trcend(obj,mod);        break;   
    }
  
/*  
  if ( getenv("DSPTEST") )
  {
    switch ( phase )
    {
      case 'B' : strcpy(msg,"start of function");            break;   
      case 'R' : strcpy(msg,"recover in function");          break;   
      case 'E' : strcpy(msg,"end of function");              break;   
      default  : strcpy(msg,"undefined use of etrace");
    }
#ifdef _WINDOWS
    {
      char *cpath;
    
      if ( cpath = getenv("DSPFILE") )
      {
        short int handle;
        
        if ( (handle = _open(cpath,(int)(O_WRONLY | O_APPEND  | O_CREAT ),
	  		     S_IWRITE                                )) > 0 )
        {
          memset(string,0,sizeof(string));
          string[0] = '\015';
          string[1] = '\012';
          gvtxstb(string+2,obj,8);
          string[10] = '-';
          string[11] = ' ';
          strcat(strcat(gvtxstb(string+12,mod,ID_SIZE)," : "),msg);
          _write(handle,string,strlen(string));
          _close(handle);
        }
      }  
#ifdef _ADK2
      else
      {
        MessBox svmbinst(NULL,WB_OK_CANCEL | WB_DEF_OK,
                         mod,msg);
        svmbinst.Execute();
      }
#endif
    }  
#else
    {
      strcat(strcat(strcpy(string,mod)," : "),msg);
      puts(string);
    }  
#endif
  }
*/

}

/******************************************************************************/
/**
\brief  TraceMessage - 




\param  errvar1 - First error variable
\param  errvar2 - Second error variable
\param  errvar3 - Third error variable
\param  errvar4 - Fourth error variable
\param  errvar5 - Fifth error variable
\param  errvar6 - Sixth error variable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TraceMessage"

void Error :: TraceMessage (char *errvar1, char *errvar2, char *errvar3, char *errvar4, char *errvar5, char *errvar6 )
{
  int        err_no;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
    
  err_no = error;
  ResetError();
  SetError(USHORTMAX,NULL,NULL);
  
  type  = 'M';
  SetErrorVariable(1,errvar1);
  SetErrorVariable(2,errvar2);
  SetErrorVariable(3,errvar3);
  SetErrorVariable(4,errvar4);
  SetErrorVariable(5,errvar5);
  SetErrorVariable(6,errvar6);
  WriteError();
  
  ResetError();
  SetError(err_no,NULL,NULL);

ENDSEQ

}

/******************************************************************************/
/**
\brief  WriteError - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteError"

void Error :: WriteError ( )
{


  SetupErrText(error_srce);
  if ( error_handle )
    error_handle->WriteError(this);
  else
    ErrorHandle().WriteError(this);


}

/******************************************************************************/
/**
\brief  operator= - Assign error object

        The  function assigns all  attributes of the  error object passed to the
        current error object. It can be used instaed of the Copy() function.

\return err_ref - Reference to an error object

\param  err_obj - Error object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

Error &Error :: operator= (Error &err_obj )
{

  Copy(err_obj);
  
  meta_error = err_obj.meta_error;
  
  error_handle = err_obj.error_handle;
  error_srce = err_obj.error_srce;
  throw_exception = err_obj.throw_exception;
  thread_id = err_obj.thread_id;
  return(*this);
}

/******************************************************************************/
/**
\brief  ~Error - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~Error"

     Error :: ~Error ( )
{

  if ( error_handle )
    error_handle->RemoveError(this);

}


