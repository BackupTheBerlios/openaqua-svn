/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    ErrorHandle

\brief    Error handle


\date     $Date: 2006/08/28 12:02:39,84 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ErrorHandle_HPP
#define   ErrorHandle_HPP

class     ErrorHandle;
#include "csosdll.h"

#ifndef   DLL_Error_HPP
#define   DLL_Error_HPP
#include  <sError.hpp>
#include  <sDLL.h>
#endif
class     CTX_Base;
#include  <sError.hpp>
#include  <sErrorMessage.hpp>
#include  <sRessourceLock.hpp>
#pragma pack(8)

class  ErrorHandle :public RessourceLock
{
protected  :         DLL(Error)                                   error_list;                                                // 
protected  :         char                                         language[20];                                              // 
protected  :         logical                                      gui_message;                                               // 
protected  :         char                                         reserved[11];                                              // 
protected  :         char                                         display;                                                   // 
protected  :         ErrorMessage                                 message;                                                   // 
protected  :         char                                         cpath[128];                                                // 
protected  :         logical                                      busy;                                                      // 
protected  :         CTX_Base                                    *context;                                                   // 

public     :
                     DLL(Error)                                  &get_error_list() { return(error_list); }
                     logical                                      get_gui_message() { return(gui_message); }
                     char                                        *get_cpath() { return(cpath); }
                     logical                                      get_busy() { return(busy); }
                     CTX_Base                                    *get_context() { return(context); }
public     :                  SOSImpExp             void ActivateGUIMessages ( );
public     :                  SOSImpExp             void AddError (Error *error_obj );
public     : virtual          SOSImpExp             logical DisplayMessage (Error *error_obj );
public     :                  SOSImpExp                  ErrorHandle ( );
public     :                  SOSImpExp             logical GUIMessagesActivated ( );
public     : virtual          SOSImpExp             logical GetDecision (Error *error_obj );
public     : virtual          SOSImpExp             char GetError (Error *error_obj, void *error_source );
public     : virtual          SOSImpExp             int32 GetErrorHelpID (Error *error_obj );
public     : virtual          SOSImpExp             void InsertStatField ( );
public     :                  SOSImpExp             void OutputMessage (char *display_name, char *message_type, char *string );
public     :                  SOSImpExp             void RemoveError (Error *error_obj );
public     : virtual          SOSImpExp             void RemoveStatField ( );
public     :                  SOSImpExp             void ResetAllErrors ( );
public     :                                        logical SetBusy (logical busy_opt );
public     :                  SOSImpExp             void SetLanguage (char *err_lang );
public     : virtual          SOSImpExp             void SetStatField (char *string );
public     : virtual          SOSImpExp             void SetStatText (char *string );
public     :                                        void SetTracePath (char *path );
public     : virtual          SOSImpExp             logical ShowMessage (Error *error_obj );
public     : virtual          SOSImpExp             void WriteError (Error *error_obj );
public     :                  SOSImpExp             logical WriteProtocol (Error *error_obj, char *prot_file );
public     :                  SOSImpExp                  virtual ~ErrorHandle ( );
};

#pragma pack()
#endif
