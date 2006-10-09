/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    CClient

\brief    


\date     $Date: 2006/06/25 16:57:20,92 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CClient_HPP
#define   CClient_HPP

class     CClient;

class     CSA_Handle;
class     CS_Handle;
class     DBObjectHandle;
class     Error;
class     SC_Handle;
class     Services;
class     node;
#include  <cPIACC.h>
#include  <sCSHandle.hpp>
#include  <sClientConnection.hpp>
#include  <sHandleInfo.hpp>
#include  <sInstance.hpp>
#include  <sObjectReference.hpp>
#include  <sReferenceObject.hpp>
#pragma pack(8)

class  CClient :public CSHandle,
public ClientConnection,
public ObjectReference
{
protected  :         Services                                    *services;                                                  // 
protected  :         ApplicationTypes                             appl_type;                                                 // 

public     :
                     Services                                    *get_services() { return(services); }
public     :                  OPAImpExp             void ActivateGUIError ( );
public     :                  OPAImpExp             logical BackupDB (char *cpath, char *target, int32 wait_sec=300 );
public     :                  OPAImpExp                  CClient (char *inipath, char *application_name=NULL, char *progpath=NULL, ApplicationTypes application_type=APT_Console );
public     :                  OPAImpExp                  CClient ( );
public     : virtual                                void CSAClosed (char *string );
public     :                  OPAImpExp             logical CacheConnection (char *cache_string=NULL );
public     :                  OPAImpExp             logical CheckDB (char *dict_path, char *cpath, CheckOptions check_opts, char *source, int32 wait_sec=300 );
public     :                  OPAImpExp             logical Connect (char *server_name, uint32 host_port=6123, char *cache_string=NULL );
public     :                  OPAImpExp             logical DictDisplay (char *cpath, char *ppath );
public     :                  OPAImpExp             void Disconnect ( );
public     :                  OPAImpExp             logical Exist (char *cpath, char chkopt=AUTO );
public     :                                        logical FillHandleInfo (HandleInfo &hi );
public     :                  OPAImpExp             CS_Handle *GetClientHandle (int32 indx0 );
public     :                  OPAImpExp             CS_Handle *GetClientHandle (CS_Handle *ch, int32 indx0 );
public     :                  OPAImpExp             Error *GetDBError ( );
public     :                                        logical GetDSResult (DataSourceHandle *ds_handle );
public     :                  OPAImpExp             char *GetDataSource (int32 indx0 );
public     :                  OPAImpExp             logical GetHandleInfo (CS_Handle *ch, HandleInfo &hi );
public     :                  OPAImpExp             MachineTypes GetMachineType (MachineTypes machtype );
public     :                  OPAImpExp             int32 GetPointerSize (int32 pointer_size );
public     :                  OPAImpExp             char *GetServerVariable (char *var_name );
public     :                  OPAImpExp             char *GetServerVersion ( );
public     : virtual                                logical InitConnection ( );
public     :                  OPAImpExp             void Initialize (char *inipath, char *application_name=NULL, char *progpath=NULL, ApplicationTypes application_type=APT_Console, logical init_services=YES );
public     :                  OPAImpExp             logical IsConnected ( );
public     :                  OPAImpExp             logical KillClient (int32 client_id, int32 wait_sec=300, logical send_message=YES );
public     :                                        logical PackDatabase (char *cpath, char *temp_path );
public     :                  OPAImpExp             logical RestoreDB (char *cpath, char *source, int32 wait_sec=300 );
public     :                  OPAImpExp             char *SayHello (void *testdata, uint32 size );
public     :                  OPAImpExp             logical SendClientMessage (int32 client_id, char *mtext, char *mtitle, uint8 mtype );
public     :                  OPAImpExp             logical SendDummy ( );
public     :                  OPAImpExp             logical SetClientName ( );
public     :                  OPAImpExp             logical SetServerVariable (char *var_name, char *var_string );
public     :                                        logical SetupDataSource (DataSourceHandle *ds_handle );
public     :                  OPAImpExp             logical ShutDown (logical close_system=YES );
public     :                                        logical StartPause (int32 wait_sec=300 );
public     :                  OPAImpExp             logical StatDisplay (char *cpath, char *ppath );
public     :                                        void StopPause ( );
public     :                  OPAImpExp             logical SysInfoDisplay (char *cpath, char *ppath );
public     : virtual          OPAImpExp                  ~CClient ( );
};

#pragma pack()
#endif
