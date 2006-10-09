/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    CS_Server

\brief    


\date     $Date: 2006/03/12 19:19:45,93 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CS_Server_HPP
#define   CS_Server_HPP

class     CS_Server;

#include  <sDLL.h>
class     CS_ServerClient;
#include  <sCS_Connection.hpp>
#include  <sCS_ServerClient.hpp>
#include  <sEvent.hpp>
#include  <sRessourceLock.hpp>
#include  <svcls.hpp>
#include  <swinsock.hpp>
#pragma pack(8)

class  CS_Server :public vcls
{
protected  :         SOCKET                                       sock ATTR_ALIGN(4);                                        
protected  :         DLL(CS_ServerClient)                        *clients;                                                   
protected  :         RessourceLock                               *lock;                                                      
protected  :         logical                                      threadTerm;                                                
protected  :         uint32                                       nextCID;                                                   
protected  :         int16                                        last_error;                                                
public     :         int64                                        server_id;                                                 
protected  :         logical                                      started;                                                   
protected  :         logical                                      threadServer;                                              
protected  :         Event                                        term_event;                                                

public     :
                     DLL(CS_ServerClient)                        *get_clients() { return(clients); }
                     logical                                      get_started() { return(started); }
public     :                                     logical AddClient (CS_ServerClient *client );
public     :         SOS7ImpExp                                          CS_Server ( );
public     : virtual SOS7ImpExp                  logical CheckTimeout ( );
public     : virtual SOS7ImpExp                  CS_ServerClient *CreateClient ( );
public     :                                     CS_ServerClient *FindClient (uint32 connect_id );
public     :                                     int16 GetLastError ( );
protected  :         SOS7ImpExp                  void Initialize (CS_ServerClient *server_client );
public     :         SOS7ImpExp                  logical IsRunning ( );
public     :                                     logical RemClient (CS_ServerClient *client );
public     : virtual SOS7ImpExp                  void RemoveClient (CS_ServerClient *client );
public     :                                     logical RemoveClients ( );
protected  :                                     logical ServerThread ( );
public     :         SOS7ImpExp                  int32 Start (int16 wPort );
public     :         SOS7ImpExp                  void Stop ( );
public     : virtual SOS7ImpExp                                          ~CS_Server ( );
};

#pragma pack()
#endif
