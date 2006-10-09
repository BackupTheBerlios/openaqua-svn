/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    CServer

\brief    


\date     $Date: 2006/03/12 19:12:39,10 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CServer_HPP
#define   CServer_HPP

class     CServer;

#include  <sDLL.h>
class     ServerConnection;
#ifndef   DLL_DictDescriptor_HPP
#define   DLL_DictDescriptor_HPP
#include  <sDictDescriptor.hpp>
#include  <sDLL.h>
#endif
class     CClient;
class     CS_ServerClient;
class     SC_Dictionary;
class     ServerConnection;
class     Services;
#include  <cPIACC.h>
#include  <sCS_Server.hpp>
#include  <sDictDescriptor.hpp>
#include  <sNString.hpp>
#include  <sSC_ConnectionCache.hpp>
#include  <ssvel.hpp>
#pragma pack(8)

class  CServer :public CS_Server
{
protected  :         DLL(ServerConnection)                       *client_list;                                               //
protected  :         DLL(DictDescriptor)                          dict_list;                                                 //
protected  :         Services                                    *services;                                                  //
protected  :         CClient                                     *main_client;                                               //
protected  :         logical                                      shutting_down;                                             //
protected  :         logical                                      blocking;                                                  //
protected  :         SC_ConnectionCache                           connection_cache;                                          //

public     :
                     DLL(DictDescriptor)                         &get_dict_list() { return(dict_list); }
                     Services                                    *get_services() { return(services); }
                     CClient                                     *get_main_client() { return(main_client); }
                     logical                                      get_shutting_down() { return(shutting_down); }
                     logical                                      get_blocking() { return(blocking); }
                     SC_ConnectionCache                          &get_connection_cache() { return(connection_cache); }
public     :                                     void Block ( );
public     :         opa7ImpExp                                          CServer (char *inipath, char *prog_path );
public     : virtual opa7ImpExp                  logical CheckTimeout ( );
public     : virtual opa7ImpExp                  CS_ServerClient *CreateClient ( );
public     :                                     char *GetCatlgName (char *sym_nams, char *cpath, int32 maxlen );
public     :                                     ServerConnection *GetClientHandle (int32 indx0 );
public     :                                     logical KillClient (int32 sender, int32 client_id, int32 wait_sec=300, logical send_message=YES );
public     :                                     SC_Connection *ProvideConnection (ServerConnection *sconnection, char *connection_string );
public     :         opa7ImpExp                  logical ProvideDict (char *cpath, uint16 version, SC_Dictionary *sc_dict, PIACC accopt );
public     :         opa7ImpExp                  logical ReleaseDict (SC_Dictionary *dict_client );
public     :                                     void RemoveClient (CS_ServerClient *server_client );
public     :                                     logical SendClientMessage (int32 sender, int32 client_id, char *mtext, char *mtitle, uint8 mtype );
public     :         opa7ImpExp                  logical Start (int16 wPort );
public     :                                     void StartDBClients ( );
public     :         opa7ImpExp                  void Stop ( );
public     :                                     logical StopDBClients (int32 sender, char *cpath, NString &nstring, int32 wait_sec=300 );
public     :                                     void Unblock ( );
public     : virtual opa7ImpExp                                          ~CServer ( );
};

#pragma pack()
#endif
