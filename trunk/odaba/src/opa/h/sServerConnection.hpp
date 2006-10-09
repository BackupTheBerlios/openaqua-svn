/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ServerConnection



\date     $Date: 2006/03/12 19:13:51,90 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ServerConnection_HPP
#define   ServerConnection_HPP

class     ServerConnection;

class     CS_Handle;
class     CS_Message;
class     CServer;
class     IFClass;
class     SC_Connection;
class     SC_Database;
class     SC_Dictionary;
#include  <cPIACC.h>
#include  <sCSInstanceList.hpp>
#include  <sCS_ServerClient.hpp>
#include  <sCheckOptions.hpp>
#include  <sNString.hpp>
#include  <sSC_Handle.hpp>
#pragma pack(8)

class  ServerConnection :public SC_Handle,
public CS_ServerClient
{
protected  :         IFClass                                     *function_table ATTR_ALIGN(4);                              //
protected  :         CSInstanceList                               send_parms;                                                //
protected  :         CSInstanceList                               send_result;                                               //
protected  :         CSInstanceList                               rec_parms;                                                 //
protected  :         CSInstanceList                               rec_result;                                                //
protected  :         logical                                      error_check;                                               //
protected  :         CServer                                     *odaba_server;                                              //
protected  :         char                                         user_name[41];                                             
protected  :         char                                         client_name[41];                                           //
protected  :         SC_Connection                               *sc_connection;                                             //

public     :
                     IFClass                                     *get_function_table() { return(function_table); }
                     CSInstanceList                              &get_send_parms() { return(send_parms); }
                     CSInstanceList                              &get_send_result() { return(send_result); }
                     CSInstanceList                              &get_rec_parms() { return(rec_parms); }
                     CSInstanceList                              &get_rec_result() { return(rec_result); }
                     logical                                      get_error_check() { return(error_check); }
                     CServer                                     *get_odaba_server() { return(odaba_server); }
                     char                                        *get_user_name() { return(user_name); }
                     char                                        *get_client_name() { return(client_name); }
                     SC_Connection                               *get_sc_connection() { return(sc_connection); }
public     :                                     logical BackupDB (char *cpath, char *target, int32 wait_sec=300 );
public     :                                     logical CacheConnection (char *connection_string );
public     :                                     logical CheckDB (SC_Database *sc_database, CheckOptions check_opts, char *source, CSInstanceList *result, int32 wait_sec=300 );
public     :                                     logical CheckDB (DictionaryHandle &dict_hdl, char *cpath, CheckOptions check_opts, char *source, CSInstanceList *result, int32 wait_sec=300 );
public     :                                     logical CheckDB (char *dict_path, char *cpath, CheckOptions check_opts, char *source, CSInstanceList *result, int32 wait_sec=300 );
public     :                                     logical Execute (uint32 dwServiceClass, uint32 dwServiceFunc, CS_Message *cpParams, CS_Message *cpResult, logical *errptr );
public     :                                     logical FillDSResult (CSInstanceList *result, char *data_source_name );
public     :                                     logical FireEvent (SC_Handle *sc_handle, CSA_Events event_id, char *parmstring );
public     :                                     void ForceClose ( );
public     :                                     logical GenerateEvent (uint32 dwServiceFunc, void *cso_ptr, CSInstanceList *csparms );
public     : virtual                             char *GetName ( );
public     : virtual                             char *GetTypeName ( );
public     :                                     logical IsCached ( );
public     :                                     SC_Handle *IsUsingDB (char *cpath );
public     :                                     logical KillClient ( );
public     :                                     SC_Dictionary *ProvideDict (int64 client_handle, char *cpath, uint16 version, PIACC accopt );
public     :                                     void ReleaseConnection ( );
public     :                                     logical ReleaseDict (CS_Handle *handle );
public     :                                     logical ReleaseDict (SC_Dictionary *dict_client );
public     :                                     logical RestoreDB (char *cpath, char *source, NString &nresult, int32 wait_sec=300 );
public     :                                     logical SendCSMessage (CS_Handle *handle, uint32 dwServiceClass, uint32 dwServiceFunc );
public     :                                     logical SendClientMessage (char *mtext, char *mtitle, uint8 mtype );
public     :                                                             ServerConnection (CServer *cserver );
public     :                                     logical SetClientName (char *string );
public     : virtual                                                     ~ServerConnection ( );
};

#pragma pack()
#endif
