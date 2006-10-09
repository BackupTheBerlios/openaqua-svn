/********************************* Class Source Code ***************************/
/**
\package  Utilities - 
\class    WinODABAService

\brief    


\date     $Date: 2006/07/16 15:28:05,90 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "WinODABAService"

#include  <puti.h>
#include  <sOService.hpp>
#include  <sWinODABAService.hpp>


/******************************************************************************/
/**
\brief  ServiceContinue - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ServiceContinue"

void WinODABAService :: ServiceContinue ( )
{

  odaba_server.Continue();
  OService::ServiceContinue();

}

/******************************************************************************/
/**
\brief  ServicePause - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ServicePause"

void WinODABAService :: ServicePause ( )
{

  if ( !odaba_server.Pause() )
    OService::ServicePause();

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

void WinODABAService :: ServiceRun (DWORD dwArgc, char **pszArgv )
{
  int               portnr = 6123;
  char             *port;
BEGINSEQ
  if ( !(ini_file = GetPosParm(command_parms,1,' ',YES)) )
    ini_file = strdup("server.ini");
  if ( port = GetPosParm(command_parms,2,' ',YES) )
    portnr = atoi(port);
    
  odaba_server.Open(ini_file,NULL);
  
  OService::ServiceRun(dwArgc,pszArgv);
  if ( odaba_server.Start(portnr) )
    LogEventMsg(ServiceName(),"Could not start server - see error log for details", EVENTLOG_ERROR_TYPE );
  else
  {
    SetAcceptPauseContinue(YES);
    SetAcceptStop(YES);
    SetAcceptShutdown(YES);
    SDBError().TraceMessage("ODABA Server started with",ini_file,"on port",port ? port : "6123");
    LogEventMsg( ServiceName(), "ODABA Server started",EVENTLOG_INFORMATION_TYPE);
    while ( odaba_server.IsRunning() )
    {
      Sleep(5000);
    }
//  RefreshWaithint(10000);
  }

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ServiceStop - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ServiceStop"

void WinODABAService :: ServiceStop ( )
{

  SetAcceptPauseContinue(NO);
  SetAcceptStop(NO);
  SetAcceptShutdown(NO);
  odaba_server.Stop();

  if ( ini_file )
    free(ini_file);

  ini_file = NULL;

  OService::ServiceStop();

}

/******************************************************************************/
/**
\brief  SetCommandParms - 



\param  parm_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCommandParms"

void WinODABAService :: SetCommandParms (char *parm_string )
{

  if ( command_parms )
    free(command_parms);
  command_parms = strdup(parm_string ? parm_string : "");

}

/******************************************************************************/
/**
\brief  WinODABAService - 



\param  service_name - 
\param  display_name - 
\param  description - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WinODABAService"

     WinODABAService :: WinODABAService (char *service_name, char *display_name, char *description )
                     : OService(service_name,display_name,description),
  odaba_server(),
  ini_file(NULL),
  command_parms(NULL)
{



}

/******************************************************************************/
/**
\brief  ~WinODABAService - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~WinODABAService"

     WinODABAService :: ~WinODABAService ( )
{

  if ( command_parms )
    free(command_parms);
  command_parms = NULL;

  if ( ini_file )
    free(ini_file);
  ini_file = NULL;


}


