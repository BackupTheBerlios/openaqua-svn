/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    OService



\date     $Date: 2006/05/20 13:27:13,03 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OService_HPP
#define   OService_HPP

#include "csosdll.h"
class     OService;

class     OService;
#pragma pack(8)

class  OService
{
protected  : static  OService                                    *service_item;                                              
protected  :         char                                        *serviceName;                                               
protected  :         char                                        *serviceDisplayName;                                        
protected  :         char                                        *serviceDescription;                                        
protected  :         DWORD                                        serviceControlsAccepted;                                   
protected  :         SERVICE_STATUS                               serviceStatus;                                             
protected  :         SERVICE_STATUS_HANDLE                        serviceStatusHandle;                                       
public     :         DWORD                                        serviceLastError;                                          
protected  : static  logical                                      servicesRunning;                                           

public     :
                     OService                                    *get_service_item() { return(service_item); }
public     :                  SOSImpExp             logical Continue ( );
public     :                  SOSImpExp             logical ControlService (DWORD dwCtrlCode );
public     :                  SOSImpExp             logical Install (char *szUser, char *szPassword, DWORD dwStartType, char *arg_string );
public     :                                        logical IsRunning (char *service_name, char *program, char *parm1=NULL, char *parm2=NULL, char *parm3=NULL );
public     :                  SOSImpExp             logical IsStarting ( );
public     :                  SOSImpExp             logical IsWinNT ( );
public     : static           SOSImpExp             logical __cdecl LogEventMsg (char *szAppName, char *szMsg, WORD wEventLogType );
public     :                  SOSImpExp                  OService (char *szServiceName, char *szServiceDisplayName, char *szServiceDescription );
public     :                  SOSImpExp                  OService ( );
public     :                  SOSImpExp             logical Pause ( );
public     :                  SOSImpExp             logical RefreshStatus ( );
public     :                  SOSImpExp             logical RefreshWaithint (DWORD dwWaithint );
public     :                  SOSImpExp             logical ReportStatus (DWORD dwState, DWORD dwExitcode, DWORD dwWaithint );
public     : virtual          SOSImpExp             void ServiceContinue ( );
public     :                  SOSImpExp             void ServiceCtrl (DWORD dwCtrlCode );
public     : virtual          SOSImpExp             void ServiceCustom (DWORD dwCtrlCode );
public     : virtual          SOSImpExp             void ServiceInterrogate ( );
public     : virtual          SOSImpExp             void ServicePause ( );
public     : virtual          SOSImpExp             void ServiceRun (DWORD dwArgc, char **pszArgv );
public     : virtual          SOSImpExp             void ServiceShutdown ( );
public     : virtual          SOSImpExp             void ServiceStop ( );
public     :                  SOSImpExp             void SetAcceptPauseContinue (logical fAccept );
public     :                  SOSImpExp             void SetAcceptShutdown (logical fAccept );
public     :                  SOSImpExp             void SetAcceptStop (logical fAccept );
public     :                  SOSImpExp             void SetIsInteractive (logical fInteractive );
public     :                  SOSImpExp             logical SetServiceName (char *szName );
public     :                  SOSImpExp             logical Start (DWORD dwArgc, char **pszArgv );
public     :                  SOSImpExp             logical Stop ( );
public     :                  SOSImpExp             logical Uninstall ( );
public     : static           SOSImpExp             logical __cdecl WinServiceMain ( );
public     : static                                 void __cdecl serviceCtrl (void *pCaller, DWORD dwCtrlCode );
public     : static                                 void __cdecl serviceMain (DWORD dwArgc, char **pszArgv );
public     :                  SOSImpExp                  ~OService ( );
public     :                                        char *ServiceName ( ){

  return serviceName;

}

};

#pragma pack()
#endif
