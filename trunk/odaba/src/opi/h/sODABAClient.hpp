/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:09:46,17}|(REF)
\class    ODABAClient

\brief    ODABA client
          To  run  client  server  applications  you  must create a ODABA client
          instance.  To support several connections to different servers you can
          create one or more clients within your application.
          When  connecting to different  servers you must  create one client for
          each  server.  You  can  open  several  clients in an application. The
          first  client, however, is considered to  be the main client. The main
          client  should  be  the  last  client  closed in an application. After
          closing  the main client you can open another main client. Since there
          is no hierarchy defined between clients the system will not check 
          The  main  client  registers  the  process and activates the error log
          file.  It opens the  system database for  providing error messages and
          the  data  catalogue  if  one  has  been  specified  in  the  system 
          environment  (see  ODABAClient  constructor).  These  information  are
          described in an ini-file, which can be passed to the client.
          For  initializing and registring the  process properly a client should
          be created also for locally running applications.

\date     $Date: 2006/03/12 19:10:00,95 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODABAClient_HPP
#define   ODABAClient_HPP

class     ODABAClient;

class     CClient;
class     DBObjectHandle;
class     DatabaseHandle;
class     Error;
#include  <cApplicationTypes.h>
#include  <cPIACC.h>
#include  <sCheckOptions.hpp>
#include  <sODABAClient.hpp>
#include  <sObjectReferenceHandle.hpp>
#pragma pack(8)

class  ODABAClient :public ObjectReferenceHandle
{

public     :
public     :         OPI7ImpExp                  void ActivateGUIMessages ( );
public     :         OPI7ImpExp                  logical BackupDB (char *cpath, char *target, int32 wait_sec=300 );
public     :         OPI7ImpExp                  logical CheckDB (char *dict_path, char *cpath, CheckOptions check_opts, char *source, int32 wait_sec=300 );
public     :                                     logical Close ( );
public     :                                     logical CloseDataSource (DBObjectHandle &dbo_handle );
public     :         OPI7ImpExp                  logical Connect (char * server_name, uint32 host_port=6123, char *cache_string=NULL );
public     :         OPI7ImpExp                  logical DictDisplay (char *dbpath, char *ppath );
public     :         OPI7ImpExp                  void Disconnect ( );
public     :         OPI7ImpExp                  logical Exist (char *cpath );
public     :         OPI7ImpExp                  CClient *GetClientPtr ( ) const;
public     :                                     int32 GetConnectionID ( );
public     :         OPI7ImpExp                  Error *GetDBError ( );
public     :         OPI7ImpExp                  char *GetDataSource (int32 indx0 );
public     :         OPI7ImpExp                  char *GetHost ( );
public     :         OPI7ImpExp                  uint32 GetPort ( );
public     :         OPI7ImpExp                  char *GetServerVariable (char *var_name );
public     :         OPI7ImpExp                  void Initialize (char *inipath, char *application_name=NULL, char *progpath=NULL, ApplicationTypes application_type=APT_Console, logical init_services=YES );
public     :         OPI7ImpExp                  logical IsConnected ( );
public     :         OPI7ImpExp                  logical KillClient (int32 client_id, int32 wait_sec=300, logical send_message=YES );
public     :         OPI7ImpExp                                          ODABAClient (char *inipath, char *application_name=NULL, char *progpath=NULL, ApplicationTypes application_type=APT_Console );
public     :         OPI7ImpExp                                          ODABAClient ( );
public     :         OPI7ImpExp                                          ODABAClient (const ODABAClient &client_refc );
public     :         OPI7ImpExp                                          ODABAClient (CClient *cclient_ptr );
public     :         OPI7ImpExp                  logical Open (char *inipath, char *application_name=NULL, char *progpath=NULL, ApplicationTypes application_type=APT_Console );
public     :         OPI7ImpExp                  logical Open (const ODABAClient &client_refc );
public     :         OPI7ImpExp                  logical Open (CClient *cclient_ptr );
public     :                                     DBObjectHandle *OpenDataSource (char *datasource_name, PIACC accopt );
public     :         OPI7ImpExp                  logical PackDatabase (char *cpath, char *temp_path=NULL );
public     :         OPI7ImpExp                  logical RestoreDB (char *cpath, char *source, int32 wait_sec=300 );
public     :         OPI7ImpExp                  char *SayHello (void *testdata, uint32 size );
public     :         OPI7ImpExp                  logical SendClientMessage (int32 client_id, char *mtext, char *mtitle=NULL, char mtype=0 );
public     :         OPI7ImpExp                  logical SetServerVariable (char *var_name, char *var_string );
public     :         OPI7ImpExp                  logical ShutDown (char close_system=YES );
public     :         OPI7ImpExp                  logical StartPause (int32 wait_sec=300 );
public     :         OPI7ImpExp                  logical StatDisplay (char *dbpath, char *ppath );
public     :         OPI7ImpExp                  void StopPause ( );
public     :         OPI7ImpExp                  logical SysInfoDisplay (char *dbpath, char *ppath );
public     :                                     NOTYPE operator bool ( );
public     :         OPI7ImpExp                  ODABAClient &operator= (ODABAClient &client_ref );
public     :         OPI7ImpExp                                          ~ODABAClient ( );
};

#pragma pack()
#endif
