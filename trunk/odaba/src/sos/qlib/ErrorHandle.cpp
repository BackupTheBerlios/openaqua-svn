/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    ErrorHandle

\brief    Error handle


\date     $Date: 2006/08/28 12:02:44,95 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ErrorHandle"

#include  <fileacc.h>
#include  <pdefault.h>
#include  <sCTX_Base.hpp>
#include  <sError.hpp>
#include  <sErrorMessage.hpp>
#include  <sNString.hpp>
#include  <sProcessInfo.hpp>
#include  <sThreadEntry.hpp>
#include  <sErrorHandle.hpp>


/******************************************************************************/
/**
\brief  ActivateGUIMessages - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateGUIMessages"

void ErrorHandle :: ActivateGUIMessages ( )
{

  if ( this )
    gui_message = YES;

}

/******************************************************************************/
/**
\brief  AddError - 



\param  error_obj - Error object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddError"

void ErrorHandle :: AddError (Error *error_obj )
{

  ILock();
  
  if ( this && error_obj )
  {
    if ( error_obj->get_error_handle() != this )
      error_obj->SetHandle(this);
    error_list.AddTail(error_obj);
  }

  IUnlock();

}

/******************************************************************************/
/**
\brief  DisplayMessage - Display message
        The  function allows displaying a message for a signaled or passed error
        code.  The message is written to  the protocol file (protocol.lst) which
        is stored in the folder located by the TRACE variable. 
        When  the  gui-option  is  set  (-> ActivateGUIMessage()) the massege is
        also displayed in a message box.
        The  function  can  be  overloaded  in a more specifib application error
        handle.

\return term - Success

\param  error_obj - Error object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayMessage"

logical ErrorHandle :: DisplayMessage (Error *error_obj )
{
  char         string[129];
  char         string1[10];
  char         buffer[sizeof(message.text)+1];
  ProcessInfo *procinfo;
BEGINSEQ
  if ( TestSysVariable("SUPRESS_ERRORS","YES") )     LEAVESEQ
    
  procinfo = ThreadEntry::GetCurProcInfo();
  if ( procinfo )
    WriteProtocol(error_obj,procinfo->GetProtocolFile());
    
  if ( error_obj )
    message.SetData(error_obj);
    
  if ( !gui_message )                                
  {
    if ( TestSysVariable("NO_CONSOLE_MESSAGES","YES") ) LEAVESEQ

    puts(gvtxbts(buffer,message.text,StringLength(message.text,sizeof(message.text))));                         
    LEAVESEQ
  }
  if ( gui_message != YES )                          // temporary enabled
    gui_message = NO;

#ifndef __unix__
  int       type = MB_OK | MB_TOPMOST;
  
  if ( error_obj )
    switch ( error_obj->type )
    {
      case  'D' : type = MB_OKCANCEL; 
      case  'M' : type |= MB_ICONQUESTION;         break;
      case  'S' : 
      case  'I' : type |= MB_ICONINFORMATION;      break;
      case  'W' : type |= MB_ICONWARNING;          break;
      default   : type |= MB_ICONERROR;
    }
  else
    type = MB_ICONERROR;
    
  gvtxbts(string,message.component,19);
  strcat(string," ");
  strcat(string,gvtxbts(string1,message.error_code,4));
  MessageBox(NULL, message.text, string, type); 

#else if
// hier fehlt noch der XWIN-Teil
#endif

RECOVER

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  ErrorHandle - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ErrorHandle"

     ErrorHandle :: ErrorHandle ( )
                     : RessourceLock(NO),
  error_list(),
  gui_message(NO),
  display('A'), 
  message(),
  busy(NO),
  context(NULL)
{

  gvtxstb(language,"EN",sizeof(language));

  *cpath = 0;
//  if ( filevfd("TRACE",cpath) )
  if ( !filevfd("TRACE",cpath) )
    strcpy(cpath,"c:/odaba2/trace/");
  strcat(cpath,"error.lst");




}

/******************************************************************************/
/**
\brief  GUIMessagesActivated - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GUIMessagesActivated"

logical ErrorHandle :: GUIMessagesActivated ( )
{

  return ( this ? gui_message : UNDEF );

}

/******************************************************************************/
/**
\brief  GetDecision - 


\return cond - Return value

\param  error_obj - Error object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDecision"

logical ErrorHandle :: GetDecision (Error *error_obj )
{
  logical                 cond = NO;
  printf("\n%s\ny/n:",error_obj->get_text());
  switch ( getchar() )
  {
    case 'y' : 
    case 'Y' : 
    case 'o' : 
    case 'O' : 
    case 'j' : 
    case 'J' : 
    case 's' : 
    case 'S' : cond = YES;
               break;
    default  : cond = NO;
  }


  return(cond);
}

/******************************************************************************/
/**
\brief  GetError - 


\return err_type - Error type

\param  error_obj - Error object
\param  error_source - Handle for the error source
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetError"

char ErrorHandle :: GetError (Error *error_obj, void *error_source )
{

  *error_obj->get_text() = 0;
  return('E');

}

/******************************************************************************/
/**
\brief  GetErrorHelpID - Get help context id
        The  function  returns  a  help  context  id that can be used to call an
        online  help topic associated with the  error. Here the function returns
        0, always,
        The  function should be overloaded in  a more specific application error
        handle.

\return helpid - Context help id

\param  error_obj - Error object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetErrorHelpID"

int32 ErrorHandle :: GetErrorHelpID (Error *error_obj )
{

  return(0);

}

/******************************************************************************/
/**
\brief  InsertStatField - Insert status line field
        The  function  creates  a  field  in  the  status  line  for  displaying
        information  from the error object in the status line. The default error
        handle does not support staus line information.
        The  function should be overloaded in  a more specific application error
        handle.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertStatField"

void ErrorHandle :: InsertStatField ( )
{



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

void ErrorHandle :: OutputMessage (char *display_name, char *message_type, char *string )
{

  ILock();
  message.SetDateTime();
  message.SetData(display_name,message_type,string);
    
  ShowMessage(NULL);
  IUnlock();    


}

/******************************************************************************/
/**
\brief  RemoveError - 



\param  error_obj - Error object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveError"

void ErrorHandle :: RemoveError (Error *error_obj )
{

  ILock();
  
  if ( this && error_obj && error_list.Find(error_obj) )
  {
    error_list.RemoveAt();
    error_obj->SetHandle(NULL);
  }

  IUnlock();


}

/******************************************************************************/
/**
\brief  RemoveStatField - Remove user field from the status line
        The  function removes a  statusline field that  had been inserted before
        using  InserStatField(). The default error handle does not support staus
        line information.
        The  function should be overloaded in  a more specific application error
        handle.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveStatField"

void ErrorHandle :: RemoveStatField ( )
{



}

/******************************************************************************/
/**
\brief  ResetAllErrors - Reset all errors
        The function resets the erors for all subsystems for the given thread.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetAllErrors"

void ErrorHandle :: ResetAllErrors ( )
{
  Error  *error_obj;
  int     indx = PVN_undefined;
  while ( (++indx) < PVN_SOSSysVariables )
    if ( error_obj = &GetErrorObject((ProcessVariableNames)indx) )
      error_obj->ResetError();
  


}

/******************************************************************************/
/**
\brief  SetBusy - 


\return cond - Return value

\param  busy_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBusy"

logical ErrorHandle :: SetBusy (logical busy_opt )
{
  logical      cond;
  if ( this )
  {
    ILock();
    cond = busy;
    busy = busy_opt;
    IUnlock();
  }
  return(cond);
}

/******************************************************************************/
/**
\brief  SetLanguage - Select language for error messages
        The  function allows setting  a language for  displaying errors when the
        associated  error handle supports multilingual error messages. The exact
        language  definitions are specific for  the associated handler, however,
        the  English  language  name  is  used  in most cases. The default error
        handle does not support languages.
        The  function should be overloaded in  a more specific application error
        handle.


\param  err_lang - Error language
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLanguage"

void ErrorHandle :: SetLanguage (char *err_lang )
{

  gvtxstb(language,err_lang,sizeof(language));

}

/******************************************************************************/
/**
\brief  SetStatField - Set value in status line
        When  a  status  field  has  been  inserted  in  the  status line of the
        application  (-> InsertStatField()),  the function  will send the passed
        string  value  to  the  status  line.  The default error handle does not
        support staus line information.
        The  function should be overloaded in  a more specific application error
        handle.


\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetStatField"

void ErrorHandle :: SetStatField (char *string )
{



}

/******************************************************************************/
/**
\brief  SetStatText - Set status line text
        The  function  will  send  the  passed  string value to the default text
        field  of the status line. This  function does not require a application
        defined  field  in  the  status line as provided with InsertStatField().
        The default error handle does not support staus line information.
        The  function should be overloaded in  a more specific application error
        handle.


\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetStatText"

void ErrorHandle :: SetStatText (char *string )
{



}

/******************************************************************************/
/**
\brief  SetTracePath - Set path for error-log file
        The  function  changes  the  path  for  the  current error log-file. The
        default  ErrorHandle records  all errors  in a  file error.lst, which is
        located  in a folder addressed by the path defined in the environment or
        system  variable  TRACE.  The  function  will  change  the  settings the
        default path for the log-file.


\param  path - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTracePath"

void ErrorHandle :: SetTracePath (char *path )
{

  strcpy(cpath,path);

}

/******************************************************************************/
/**
\brief  ShowMessage - 


\return term - Success

\param  error_obj - Error object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowMessage"

logical ErrorHandle :: ShowMessage (Error *error_obj )
{
  NString      string;
  logical      term = NO;
  if ( error_obj )
    message.SetData(error_obj);
    
  string.Append(message.component,sizeof(message.component));
  string += ' ';
  string.Append(message.error_type,sizeof(message.error_type));
  string += ' ';
  string.Append(message.error_code,sizeof(message.error_code));
  string += ':';
  string += ' ';
  if ( error_obj )
    string.Append(message.text,sizeof(message.text));
  
  SystemOutput(string,NO,YES);  

  return(term);
}

/******************************************************************************/
/**
\brief  WriteError - Write error to the log-file
        The  function  writes  the  information  for  the error set in the error
        object to the log-file.
        The  function  can  be  overloaded  in a more specifib application error
        handle.


\param  error_obj - Error object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteError"

void ErrorHandle :: WriteError (Error *error_obj )
{
  char         path[256];
  Error        saverr = *error_obj;
  logical      show_errors = NO;
  ProcessInfo *procinfo;
  short        handle;
BEGINSEQ
  if ( error_obj->CheckError() )
  {
    if ( (procinfo = ThreadEntry::GetCurProcInfo()) && 
          procinfo->get_error_file() && *procinfo->get_error_file() )
    {
      strcpy(path,procinfo->get_error_file());
      strcat(strcat(path,"/"),"error.lst");
    }
    else
      strcpy(path,cpath);
    
    show_errors = TestSysVariable("SHOW_ERRORS","YES");
    *error_obj = saverr;
    
    ILock();
    if ( error_obj )
      message.SetData(error_obj);
    
#ifdef __unix__
    if ( (handle = _open (path,
			  (int)(O_RDWR | O_APPEND | O_CREAT ),
			  (S_IREAD | S_IWRITE)                    )) > 0 )
#else  
    if ( (handle = _open (path,
			  (int)(O_WRONLY | O_APPEND  | O_CREAT | O_BINARY ),
			  S_IWRITE                                )) > 0 )
#endif
    {
      _write(handle,&message,sizeof(message));
      _close(handle);
    }
    if ( show_errors )
    {
      if ( !gui_message )
        gui_message = AUTO;        // enable temporaily
      ShowMessage(NULL);
    }
    IUnlock();
    
  }

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  WriteProtocol - 


\return term - Success

\param  error_obj - Error object
\param  prot_file - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteProtocol"

logical ErrorHandle :: WriteProtocol (Error *error_obj, char *prot_file )
{
  short int               handle;
  char                    cpath[256];
  logical                 term = NO;
  ILock();
  message.SetDateTime();
  if ( error_obj )
    message.SetError(error_obj);

  if ( prot_file && *prot_file )
  {
    strcpy(cpath,prot_file);
    strcat(strcat(cpath,"/"),"protocol.lst");

#ifdef __unix__
    if ( (handle = _open (cpath,
			  (int)(O_RDWR | O_APPEND  | O_CREAT ),
			  (S_IREAD | S_IWRITE)                    )) > 0 )
#else
    if ( (handle = _open (cpath,
			  (int)(O_WRONLY | O_APPEND  | O_CREAT | O_BINARY ),
			  S_IWRITE                                )) > 0 )
#endif
    {
      _write(handle,&message,offsetof(ErrorMessage,component));
      _write(handle,message.text,StringLength(message.text,sizeof(message.text)));
      _write(handle,"\r\n",2);
      _close(handle);
    }
    IUnlock();    
  }
  ShowMessage(error_obj);   

  IUnlock();    

  return(term);
}

/******************************************************************************/
/**
\brief  ~ErrorHandle - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ErrorHandle"

     ErrorHandle :: ~ErrorHandle ( )
{
  Error   *error_obj;
  if ( this )
    while ( error_obj = error_list.GetHead() )
    {
      error_list.RemoveAt();
      error_obj->SetHandle(NULL);
    }


}


