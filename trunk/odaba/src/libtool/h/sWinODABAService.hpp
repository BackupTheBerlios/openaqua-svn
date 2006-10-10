/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:21:31,04}|(REF)
\class    WinODABAService



\date     $Date: 2006/03/12 19:21:40,04 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   WinODABAService_HPP
#define   WinODABAService_HPP

class     WinODABAService;

#include  <sODABAServer.hpp>
#include  <sOService.hpp>
class  WinODABAService :public OService
{
protected  :         ODABAServer                                  odaba_server;                                              //
protected  :         char                                        *ini_file;                                                  //
protected  :         char                                        *command_parms;                                             //

public     :
                     ODABAServer                                 &get_odaba_server() { return(odaba_server); }
                     char                                        *get_ini_file() { return(ini_file); }
                     char                                        *get_command_parms() { return(command_parms); }
public     : virtual                             void ServiceContinue ( );
public     : virtual                             void ServicePause ( );
public     : virtual                             void ServiceRun (DWORD dwArgc, char **pszArgv );
public     : virtual                             void ServiceStop ( );
public     :                                     void SetCommandParms (char *parm_string );
public     :                                                             WinODABAService (char *service_name, char *display_name, char *description );
public     :                                                             ~WinODABAService ( );
};

#endif
