#ifndef __unix__
/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    OService

\brief    


\date     $Date: 2006/07/16 15:28:56,76 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OService"

#include  <pdefault.h>
#include  <cosrvc.h>
#include  <sOService.hpp>
#include  <sOService.hpp>


/******************************************************************************/
/**
\brief  Continue - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Continue"

logical OService :: Continue ( )
{

  return (ControlService(SERVICE_CONTROL_CONTINUE));

}

/******************************************************************************/
/**
\brief  ControlService - 



\return term - Success

\param  dwCtrlCode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ControlService"

logical OService :: ControlService (DWORD dwCtrlCode )
{
  logical                 term = NO;
  SC_HANDLE               hservice= NULL;
  SC_HANDLE               hsrvmanager= NULL;
BEGINSEQ
  // Open the default, local Service Control Manager database
  hsrvmanager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
  if ( !hsrvmanager )                                ERROR

  if ( !(hservice = OpenService(hsrvmanager,serviceName,SERVICE_ALL_ACCESS)) )
                                                     ERROR
  if( !::ControlService(hservice,dwCtrlCode,&serviceStatus) ) 
                                                     ERROR
RECOVER
serviceLastError= GetLastError();
  term = YES;
ENDSEQ
if( hservice ) CloseServiceHandle(hservice);
if( hsrvmanager ) CloseServiceHandle(hsrvmanager);
  return(term);
}

/******************************************************************************/
/**
\brief  Install - 



\return term - Success

\param  szUser - 
\param  szPassword - 
\param  dwStartType - 
\param  arg_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Install"

logical OService :: Install (char *szUser, char *szPassword, DWORD dwStartType, char *arg_string )
{
  SC_HANDLE               hservice= NULL;
  SC_HANDLE               hsrvmanager= NULL;
  char                    path[2048];
  logical                 term = NO;
BEGINSEQ
  if ( !GetModuleFileName(NULL,path,2048) )          ERROR
  if ( arg_string )
    strcat(strcat(path," "),arg_string);

// Open the default, local Service Control Manager database
  if ( !(hsrvmanager = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS)) )
                                                     ERROR
  if ( !(hservice = CreateService(hsrvmanager,				
                                  serviceName,				
                                  serviceDisplayName,			
                                  SERVICE_ALL_ACCESS,		
                                  serviceStatus.dwServiceType,
                                  dwStartType,
                                  SERVICE_ERROR_NORMAL,		
                                  path,
                                  NULL,
                                  NULL,
                                  NULL,
                                  szUser,						
                                  szPassword)) )     ERROR

  if ( serviceDescription && *serviceDescription )
  {
    SERVICE_DESCRIPTION   sd;
    sd.lpDescription = serviceDescription;
    ChangeServiceConfig2(hservice,SERVICE_CONFIG_DESCRIPTION,&sd);
  }


RECOVER
serviceLastError= GetLastError();
  term = YES;
ENDSEQ
if( hservice ) CloseServiceHandle(hservice);
if( hsrvmanager ) CloseServiceHandle(hsrvmanager);
  return(term);
}

/******************************************************************************/
/**
\brief  IsRunning - Checks, whether the service is running

        The  function checks whether the service is running and returns the path
        for  the executable file (program) and  up to three parameters passed to
        the  service. All string parameters (including program) must point to an
        area  of  at  least  128  bytes. All values are returned as 0-terminated
        string with a maximum size of 127 characters.

\return cond - Return value

\param  service_name - 
\param  program - 
\param  parm1 - First Message parameter
\param  parm2 - Second message variable
\param  parm3 - Third message variable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsRunning"

logical OService :: IsRunning (char *service_name, char *program, char *parm1, char *parm2, char *parm3 )
{
  logical                 cond        = YES;
  SC_HANDLE               hservice    = NULL;
  SC_HANDLE               hsrvmanager = NULL;
  SERVICE_STATUS          st;
  char                    buffer[2048];
  LPQUERY_SERVICE_CONFIG  sc = (LPQUERY_SERVICE_CONFIG)buffer;
  DWORD                   used;
  char                   *string;
BEGINSEQ
// Open the SCM
  hsrvmanager = OpenSCManager(NULL,     // machine (NULL == local)
                              NULL,     // database (NULL == default)
                              SC_MANAGER_ALL_ACCESS );  // access required
  if ( !hsrvmanager )                                ERROR

  if ( !(hservice = OpenService(hsrvmanager,service_name,SERVICE_ALL_ACCESS)) )
                                                     ERROR
  
  if ( QueryServiceStatus(hservice,&st) )
    if ( st.dwCurrentState != SERVICE_RUNNING )      ERROR
  
  if ( !QueryServiceConfig(hservice,sc,sizeof(buffer),&used) )
                                                     ERROR
  if ( program )
  {
    *program = 0;
    if ( string = GetPosParm(sc->lpBinaryPathName,1,' ',YES) )
    {
      strncpy(program,string,127);
      free(string);
    }
  }
    
  if ( parm1 )
  {
    *parm1 = 0;
    if ( string = GetPosParm(sc->lpBinaryPathName,2,' ',YES) )
    {
      strncpy(parm1,string,127);
      free(string);
    }
  }
  if ( parm2 )
  {
    *parm2 = 0;
    if ( string = GetPosParm(sc->lpBinaryPathName,3,' ',YES) )
    {
      strncpy(parm2,string,127);
      free(string);
    }
  }
  if ( parm3 )
  {
    *parm3 = 0;
    if ( string = GetPosParm(sc->lpBinaryPathName,4,' ',YES) )
    {
      strncpy(parm3,string,127);
      free(string);
    }
  }

RECOVER
  cond = YES;
ENDSEQ
  if ( hservice )
    CloseServiceHandle(hservice);
  if ( hsrvmanager )
    CloseServiceHandle(hsrvmanager);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsStarting - 



\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsStarting"

logical OService :: IsStarting ( )
{

  return(serviceStatus.dwCurrentState == SERVICE_START_PENDING);

}

/******************************************************************************/
/**
\brief  IsWinNT - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsWinNT"

logical OService :: IsWinNT ( )
{
  OSVERSIONINFO osversioninfo;

  osversioninfo.dwOSVersionInfoSize = sizeof(osversioninfo);

  return ( !GetVersionEx(&osversioninfo) 
           ? NO : osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT);


}

/******************************************************************************/
/**
\brief  LogEventMsg - 



\return term - Success

\param  szAppName - 
\param  szMsg - 
\param  wEventLogType - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LogEventMsg"

logical __cdecl OService :: LogEventMsg (char *szAppName, char *szMsg, WORD wEventLogType )
{
logical term= NO;
BEGINSEQ
char	msgbuff[256];
HANDLE	heventsrc;
char *	strings[2];

// Use event logging to log the error
heventsrc = RegisterEventSource(NULL, szAppName);

sprintf(msgbuff, "%s", szAppName);
strings[0] = msgbuff;
strings[1] = szMsg;

if (heventsrc != NULL)
{
  ReportEvent(
    heventsrc,				// handle of event source
    wEventLogType,	           // event type
    0,						// event category
    0,						// event ID
    NULL,					// current user's SID
    2,						// strings in 'strings'
    0,						// no bytes of raw data
    (const char **)strings,	// array of error strings
    NULL);					// no raw data

  DeregisterEventSource(heventsrc);
}
else ERROR

RECOVER
term= YES;
ENDSEQ
return term;
}

/******************************************************************************/
/**
\brief  OService - 



\return term - Success
-------------------------------------------------------------------------------
\brief  i0 - 



\param  szServiceName - 
\param  szServiceDisplayName - 
\param  szServiceDescription - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OService"

     OService :: OService (char *szServiceName, char *szServiceDisplayName, char *szServiceDescription )
                     : serviceName(szServiceName),
serviceDisplayName(szServiceDisplayName),
serviceDescription(szServiceDescription),
  serviceStatus(),
  serviceStatusHandle(0),
  serviceControlsAccepted(0),
  serviceLastError(0)
{

  service_item = this;
  
  serviceStatus.dwCheckPoint= 0;
  serviceStatus.dwServiceType= SERVICE_WIN32_SHARE_PROCESS;
  SetAcceptPauseContinue(YES);
  SetAcceptShutdown(YES);
  SetAcceptStop(YES);


}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OService"

     OService :: OService ( )
                     : serviceName(NULL),
  serviceDisplayName(NULL),
  serviceDescription(NULL),
  serviceStatus(),
  serviceStatusHandle(0),
  serviceControlsAccepted(0),
  serviceLastError(0)
{

  service_item = this;

}

/******************************************************************************/
/**
\brief  Pause - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Pause"

logical OService :: Pause ( )
{

  return(ControlService(SERVICE_CONTROL_PAUSE));

}

/******************************************************************************/
/**
\brief  RefreshStatus - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RefreshStatus"

logical OService :: RefreshStatus ( )
{

 return( ReportStatus(serviceStatus.dwCurrentState,
                      serviceStatus.dwWin32ExitCode,
                      serviceStatus.dwWaitHint)     );

}

/******************************************************************************/
/**
\brief  RefreshWaithint - 



\return term - Success

\param  dwWaithint - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RefreshWaithint"

logical OService :: RefreshWaithint (DWORD dwWaithint )
{

  return( ReportStatus(serviceStatus.dwCurrentState,
                       serviceStatus.dwWin32ExitCode,
                       dwWaithint)                    );

}

/******************************************************************************/
/**
\brief  ReportStatus - 



\return term - Success

\param  dwState - 
\param  dwExitcode - 
\param  dwWaithint - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReportStatus"

logical OService :: ReportStatus (DWORD dwState, DWORD dwExitcode, DWORD dwWaithint )
{
  logical                 term = NO;
BEGINSEQ
  if ( serviceStatusHandle == NULL )                 LEAVESEQ

  // If we're in the start state then we don't want the control manager
  // sending us control messages because they'll confuse us.
  serviceStatus.dwControlsAccepted = dwState == SERVICE_START_PENDING 
                                     ? 0
                                     : serviceControlsAccepted;

  // Save the new status we've been given
  serviceStatus.dwCurrentState  = dwState;
  serviceStatus.dwWin32ExitCode = dwExitcode;
  serviceStatus.dwWaitHint      = dwWaithint;

  // Update the checkpoint variable to let the SCM know that we
  // haven't died if requests take a long time
  if ( dwState == SERVICE_RUNNING || dwState == SERVICE_STOPPED )
    serviceStatus.dwCheckPoint= 0;
  else
    serviceStatus.dwCheckPoint++;

  // Tell the SCM our new status
  if( !SetServiceStatus(serviceStatusHandle,&serviceStatus) )
  {
    char buf[1024];
    sprintf( buf, "SetServiceStatus failed with error %d.", GetLastError() );
    LogEventMsg( serviceDisplayName, buf, EVENTLOG_ERROR_TYPE );
    ERROR
  }

RECOVER
serviceLastError= GetLastError();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ServiceContinue - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ServiceContinue"

void OService :: ServiceContinue ( )
{

BEGINSEQ
  ReportStatus(SERVICE_RUNNING,NO_ERROR,0);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ServiceCtrl - 




\param  dwCtrlCode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ServiceCtrl"

void OService :: ServiceCtrl (DWORD dwCtrlCode )
{

BEGINSEQ
  switch( dwCtrlCode )
  {
    case SERVICE_CONTROL_STOP:
      serviceStatus.dwCurrentState = SERVICE_STOP_PENDING;
      ServiceStop();
      break;
  
    case SERVICE_CONTROL_PAUSE:
      serviceStatus.dwCurrentState = SERVICE_PAUSE_PENDING;
      ServicePause();
      break;
  
    case SERVICE_CONTROL_CONTINUE:
      serviceStatus.dwCurrentState = SERVICE_CONTINUE_PENDING;
      ServiceContinue();
      break;
  
    case SERVICE_CONTROL_SHUTDOWN:
      serviceStatus.dwCurrentState = SERVICE_STOP_PENDING;
      ServiceShutdown();
      break;
  
    case SERVICE_CONTROL_INTERROGATE:
      ServiceInterrogate();
      break;
    
    default:
      ServiceCustom( dwCtrlCode );
      break;

  }
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ServiceCustom - 




\param  dwCtrlCode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ServiceCustom"

void OService :: ServiceCustom (DWORD dwCtrlCode )
{



}

/******************************************************************************/
/**
\brief  ServiceInterrogate - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ServiceInterrogate"

void OService :: ServiceInterrogate ( )
{

BEGINSEQ
  ReportStatus(serviceStatus.dwCurrentState,NO_ERROR,0);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ServicePause - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ServicePause"

void OService :: ServicePause ( )
{

BEGINSEQ
  ReportStatus(SERVICE_PAUSED,NO_ERROR,0);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ServiceRun - 




\param  dwArgc - 
\param  pszArgv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ServiceRun"

void OService :: ServiceRun (DWORD dwArgc, char **pszArgv )
{

BEGINSEQ
  ReportStatus(SERVICE_RUNNING,NO_ERROR,0);


RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ServiceShutdown - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ServiceShutdown"

void OService :: ServiceShutdown ( )
{

  ServiceStop();

}

/******************************************************************************/
/**
\brief  ServiceStop - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ServiceStop"

void OService :: ServiceStop ( )
{



}

/******************************************************************************/
/**
\brief  SetAcceptPauseContinue - 




\param  fAccept - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAcceptPauseContinue"

void OService :: SetAcceptPauseContinue (logical fAccept )
{

  if ( fAccept ) 
    serviceControlsAccepted |= SERVICE_ACCEPT_PAUSE_CONTINUE;
  else 
    serviceControlsAccepted &= ~SERVICE_ACCEPT_PAUSE_CONTINUE;
  
  RefreshStatus();

}

/******************************************************************************/
/**
\brief  SetAcceptShutdown - 




\param  fAccept - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAcceptShutdown"

void OService :: SetAcceptShutdown (logical fAccept )
{

  if ( fAccept ) 
    serviceControlsAccepted |= SERVICE_ACCEPT_SHUTDOWN;
  else 
    serviceControlsAccepted &= ~SERVICE_ACCEPT_SHUTDOWN;
  
  RefreshStatus();

}

/******************************************************************************/
/**
\brief  SetAcceptStop - 




\param  fAccept - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAcceptStop"

void OService :: SetAcceptStop (logical fAccept )
{

  if ( fAccept ) 
    serviceControlsAccepted |= SERVICE_ACCEPT_STOP;
  else 
    serviceControlsAccepted &= ~SERVICE_ACCEPT_STOP;
  
  RefreshStatus();

}

/******************************************************************************/
/**
\brief  SetIsInteractive - 




\param  fInteractive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetIsInteractive"

void OService :: SetIsInteractive (logical fInteractive )
{

  if ( fInteractive ) 
    serviceStatus.dwServiceType |= SERVICE_INTERACTIVE_PROCESS;
  else 
    serviceStatus.dwServiceType &= ~SERVICE_INTERACTIVE_PROCESS;
  
  RefreshStatus();

}

/******************************************************************************/
/**
\brief  SetServiceName - 



\return term - Success

\param  szName - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetServiceName"

logical OService :: SetServiceName (char *szName )
{
  logical                 term = NO;
BEGINSEQ
  if ( servicesRunning )                             ERROR
  
  serviceName       = szName;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Start - 



\return term - Success

\param  dwArgc - 
\param  pszArgv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Start"

logical OService :: Start (DWORD dwArgc, char **pszArgv )
{
  logical              term        = NO;
  SC_HANDLE            hservice    = NULL;
  SC_HANDLE            hsrvmanager = NULL;

BEGINSEQ
// Open the default, local Service Control Manager database
  if ( !(hsrvmanager = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS)) )
                                                     ERROR

  if ( !(hservice = OpenService(hsrvmanager,serviceName,SERVICE_ALL_ACCESS)) )
                                                     ERROR

  if ( !StartService(hservice,dwArgc,(const char**)pszArgv )) 
                                                     ERROR
RECOVER
  serviceLastError= GetLastError();
  term= YES;
ENDSEQ
  if ( hservice ) 
    CloseServiceHandle(hservice);
  if( hsrvmanager ) 
    CloseServiceHandle(hsrvmanager);
  return term;
}

/******************************************************************************/
/**
\brief  Stop - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Stop"

logical OService :: Stop ( )
{

  return ControlService(SERVICE_CONTROL_STOP);

}

/******************************************************************************/
/**
\brief  Uninstall - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Uninstall"

logical OService :: Uninstall ( )
{
  logical                 term        = NO;
  SC_HANDLE               hservice    = NULL;
  SC_HANDLE               hsrvmanager = NULL;

BEGINSEQ
// Open the SCM
  hsrvmanager = OpenSCManager(NULL,     // machine (NULL == local)
                              NULL,     // database (NULL == default)
                              SC_MANAGER_ALL_ACCESS );  // access required
  if ( !hsrvmanager )                                ERROR

  if ( !(hservice = OpenService(hsrvmanager,serviceName,SERVICE_ALL_ACCESS)) )
                                                     ERROR
  if( !DeleteService(hservice) )                     ERROR
  CloseServiceHandle(hsrvmanager);

RECOVER
  serviceLastError= GetLastError();
  term = YES;
ENDSEQ
  if ( hservice ) 
    CloseServiceHandle(hservice);
  if ( hsrvmanager ) 
    CloseServiceHandle(hsrvmanager);
  return(term);
}

/******************************************************************************/
/**
\brief  WinServiceMain - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WinServiceMain"

logical __cdecl OService :: WinServiceMain ( )
{
  SERVICE_TABLE_ENTRY   *dispatchTable;
  int                    cnt  = 1;
  int                    idx  = 0;
  logical                term = NO;
BEGINSEQ
  servicesRunning= YES;

// create dispatch table with all known services

  dispatchTable= new SERVICE_TABLE_ENTRY[2];  // cnt
  dispatchTable[0].lpServiceName = service_item->serviceName;
  dispatchTable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION)ServiceMain;
  dispatchTable[1].lpServiceName = NULL;
  dispatchTable[1].lpServiceProc = NULL;

// Call the service control dispatcher with our entry table

  if ( !StartServiceCtrlDispatcher(dispatchTable) )
  {
    char buf[1024];
    sprintf( buf,"StartServiceCtrlDispatcher failed with error %d.",GetLastError());
    LogEventMsg( "OService",buf,EVENTLOG_ERROR_TYPE);
    ERROR
  }

RECOVER
term= YES;
ENDSEQ
return term;
}

/******************************************************************************/
/**
\brief  serviceCtrl - 




\param  pCaller - 
\param  dwCtrlCode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "serviceCtrl"

void __cdecl OService :: serviceCtrl (void *pCaller, DWORD dwCtrlCode )
{

  if ( service_item ) 
    service_item->ServiceCtrl(dwCtrlCode);

}

/******************************************************************************/
/**
\brief  serviceMain - 




\param  dwArgc - 
\param  pszArgv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "serviceMain"

void __cdecl OService :: serviceMain (DWORD dwArgc, char **pszArgv )
{
  OService             *srv= NULL;
BEGINSEQ
  if ( service_item )
  {
    srv= service_item;
    srv->serviceStatusHandle= RegisterServiceCtrlHandler( pszArgv[0], (LPHANDLER_FUNCTION) serviceCtrl );  
    LogEventMsg( pszArgv[0],"register serviceclass.",EVENTLOG_INFORMATION_TYPE );
  }

  if( !srv )
  {
    LogEventMsg( pszArgv[0],"Could not find serviceclass.",EVENTLOG_ERROR_TYPE );
    ERROR
  }

  if( !srv->serviceStatusHandle )
  {
    LogEventMsg( srv->serviceName,"RegisterServiceCtrlHandler failed",EVENTLOG_ERROR_TYPE);
    ERROR
  }

  if( !srv->ReportStatus( SERVICE_START_PENDING, NO_ERROR, 1000 ) )
     srv->ServiceRun(dwArgc,pszArgv);
  srv->ReportStatus( SERVICE_STOPPED, NO_ERROR,0);
RECOVER
if( srv ) srv->serviceLastError= GetLastError();
ENDSEQ

}

/******************************************************************************/
/**
\brief  ~OService - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OService"

     OService :: ~OService ( )
{



}


#endif //ndef __unix__
