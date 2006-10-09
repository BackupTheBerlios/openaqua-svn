/********************************* Class Declaration ***************************/
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

\date     $Date: 2006/08/27 14:20:48,70 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   Error_HPP
#define   Error_HPP

class     Error;
#include "csosdll.h"

#define  ERROR_TEXTL                               500
#define  ERROR_VARLEN                              80
class     CTX_Base;
class     ErrorHandle;
#include  <sError.hpp>
#include  <sRessourceLock.hpp>
#include  <ssts.hpp>
#pragma pack(8)

class  Error :public sts
{
protected  :         int                                          error;                                                     // 
public     :         char                                         modid[41];                                                 // 
public     :         char                                         objid[41];                                                 // 
public     :         char                                         proid[41];                                                 // 
public     :         char                                         err_class[40];                                             // 
protected  :         char                                         title[41];                                                 // 
public     :         logical                                      tdspl;                                                     // 
public     :         logical                                      tlist;                                                     // 
protected  :         logical                                      thier;                                                     // 
protected  :         int32                                        meta_error;                                                // 
protected  :         char                                         err_var1[81];                                              // 
protected  :         char                                         err_var2[81];                                              // 
protected  :         char                                         err_var3[81];                                              // 
protected  :         char                                         err_var4[81];                                              // 
protected  :         char                                         err_var5[81];                                              // 
protected  :         char                                         err_var6[81];                                              // 
public     :         char                                         type;                                                      // 
protected  :         char                                         text[501];                                                 // 
protected  :         ErrorHandle                                 *error_handle;                                              // 
protected  :         void                                        *error_srce;                                                // 
protected  :         logical                                      throw_exception;                                           // 
protected  :         int32                                        thread_id;                                                 // 

public     :
                     char                                        *get_title() { return(title); }
                     logical                                      get_thier() { return(thier); }
                     int32                                        get_meta_error() { return(meta_error); }
                     char                                        *get_err_var1() { return(err_var1); }
                     char                                        *get_err_var2() { return(err_var2); }
                     char                                        *get_err_var3() { return(err_var3); }
                     char                                        *get_err_var4() { return(err_var4); }
                     char                                        *get_err_var5() { return(err_var5); }
                     char                                        *get_err_var6() { return(err_var6); }
                     char                                        *get_text() { return(text); }
                     ErrorHandle                                 *get_error_handle() { return(error_handle); }
                     void                                        *get_error_srce() { return(error_srce); }
                     logical                                      get_throw_exception() { return(throw_exception); }
                     int32                                        get_thread_id() { return(thread_id); }
public     :                  SOSImpExp             int32 CheckError ( );
public     :                  SOSImpExp             void Copy (Error &err_obj );
public     :                  SOSImpExp             void CreateExceptions (logical exceptions=YES );
public     :                  SOSImpExp             logical DisplayMessage (const int16 err_code, char *errvar1=NULL, char *errvar2=NULL, char *errvar3=NULL, char *errvar4=NULL, char *errvar5=NULL, char *errvar6=NULL );
public     :                  SOSImpExp             logical DisplayMessage ( );
public     :                  SOSImpExp             logical DisplayMessage (void *error_source, const int16 err_code, char *errvar1=NULL, char *errvar2=NULL, char *errvar3=NULL, char *errvar4=NULL, char *errvar5=NULL, char *errvar6=NULL );
public     :                  SOSImpExp             logical DisplayMessage (void *error_source );
public     :                  SOSImpExp                  Error (int16 metacode, char *pid, char *errclass, char *ttext=NULL );
public     :                  SOSImpExp                  Error ( );
public     :                  SOSImpExp                  Error (Error &err_obj );
public     :                  SOSImpExp             logical GetDecision (const int16 err_code, char *errvar1=NULL, char *errvar2=NULL, char *errvar3=NULL, char *errvar4=NULL, char *errvar5=NULL, char *errvar6=NULL );
public     :                  SOSImpExp             logical GetDecision ( );
public     :                  SOSImpExp             logical GetDecision (void *error_source, const int16 err_code, char *errvar1=NULL, char *errvar2=NULL, char *errvar3=NULL, char *errvar4=NULL, char *errvar5=NULL, char *errvar6=NULL );
public     :                  SOSImpExp             logical GetDecision (void *error_source );
public     :                  SOSImpExp             int32 GetErrorHelpID ( );
public     :                  SOSImpExp             char *GetErrorText (void *error_source, const int16 err_code, char *errvar1=NULL, char *errvar2=NULL, char *errvar3=NULL, char *errvar4=NULL, char *errvar5=NULL, char *errvar6=NULL );
public     :                  SOSImpExp             char *GetErrorVariable (int8 varnum, char *inittext );
public     :                  SOSImpExp             ErrorHandle *GetHandle ( );
public     :                  SOSImpExp             char *GetText ( );
public     :                  SOSImpExp             char *GetTitle ( );
public     :                  SOSImpExp             void Initialize ( );
public     :                  SOSImpExp             void Initialize (int16 metacode, char *pid, char *errclass, char *ttext=NULL );
public     :                  SOSImpExp             void InsertStatField ( );
public     :                  SOSImpExp             logical IsGUIApplication ( );
public     :                  SOSImpExp             void OutputMessage (char *display_name, char *message_type, char *string );
public     :                  SOSImpExp             void RemoveStatField ( );
public     :                  SOSImpExp             void Reset ( );
public     :                  SOSImpExp             void ResetAllErrors ( );
public     :                  SOSImpExp             void ResetError ( );
public     :                  SOSImpExp             void ResetErrorVariables ( );
public     :                  SOSImpExp             void SetError (const int16 err_code, char *obj, char *mod );
public     :                  SOSImpExp             void SetErrorVariable (int8 varnum, char *vartext=NULL, int16 varlen=0 );
public     :                  SOSImpExp             void SetErrorVariables (int32 max_len, char *errvar1=NULL, char *errvar2=NULL, char *errvar3=NULL, char *errvar4=NULL, char *errvar5=NULL, char *errvar6=NULL );
public     :                  SOSImpExp             void SetErrorWithVariables (const int16 err_code, char *obj, char *mod, char *errvar1=NULL, char *errvar2=NULL, char *errvar3=NULL, char *errvar4=NULL, char *errvar5=NULL, char *errvar6=NULL );
public     :                  SOSImpExp             void SetHandle (ErrorHandle *error_hdl );
public     :                  SOSImpExp             void SetLanguage (char *err_lang );
public     :                  SOSImpExp             void SetSource (void *error_source );
public     :                  SOSImpExp             void SetStatField (char *string );
public     :                  SOSImpExp             void SetStatText (char *string );
public     :                  SOSImpExp             void SetText (char *err_text );
public     :                  SOSImpExp             void SetTitle (char *ttext=NULL );
public     :                  SOSImpExp             void SetTracePath (char *cpath );
public     :                  SOSImpExp             void SetType (char err_type );
public     :                  SOSImpExp             void SetupErrText (void *error_source );
public     :                  SOSImpExp             logical ShowMessage (const int16 err_code, char *errvar1=NULL, char *errvar2=NULL, char *errvar3=NULL, char *errvar4=NULL, char *errvar5=NULL, char *errvar6=NULL );
public     :                  SOSImpExp             logical ShowMessage ( );
public     :                  SOSImpExp             logical ShowMessage (void *error_source, const int16 err_code, char *errvar1=NULL, char *errvar2=NULL, char *errvar3=NULL, char *errvar4=NULL, char *errvar5=NULL, char *errvar6=NULL );
public     :                  SOSImpExp             logical ShowMessage (void *error_source );
public     :                  SOSImpExp             logical SystemCheck (logical cond, char *obj, char *mod );
public     :                  SOSImpExp             void TraceFunction (void **tptr, char *mod, char *obj, char phase );
public     :                  SOSImpExp             void TraceMessage (char *errvar1=NULL, char *errvar2=NULL, char *errvar3=NULL, char *errvar4=NULL, char *errvar5=NULL, char *errvar6=NULL );
public     :                  SOSImpExp             void WriteError ( );
public     :                  SOSImpExp             Error &operator= (Error &err_obj );
public     :                  SOSImpExp                  ~Error ( );
};

#pragma pack()
#endif
