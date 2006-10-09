/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    CS_Client

\brief    


\date     $Date: 2006/03/12 19:19:41,87 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CS_Client_HPP
#define   CS_Client_HPP

class     CS_Client;

class     CS_Message;
#include  <cMachineTypes.h>
#include  <sCS_Connection.hpp>
#include  <sEvent.hpp>
#pragma pack(8)

class  CS_Client :public CS_Connection
{
protected  :         int16                                        server_ptr_size ATTR_ALIGN(4);                             //
protected  :         MachineTypes                                 server_mtype;                                              //
protected  :         char                                        *host;                                                      //
protected  :         uint32                                       port;                                                      //
protected  :         int16                                        last_error;                                                //
protected  :         logical                                      connect_error;                                             //
protected  :         int64                                        server_id;                                                 //

public     :
                     int16                                        get_server_ptr_size() { return(server_ptr_size); }
                     MachineTypes                                 get_server_mtype() { return(server_mtype); }
public     :         SOS7ImpExp                                          CS_Client ( );
public     :         SOS7ImpExp                  logical ConnectServer (char *host_name, uint32 host_port );
public     :         SOS7ImpExp                  logical DisconnectServer ( );
protected  : virtual SOS7ImpExp                  logical DoConnect ( );
public     : virtual SOS7ImpExp                  logical Execute (uint32 dwServiceClass, uint32 dwServiceFunc, CS_Message *pParams, CS_Message *pResult, logical *pError );
public     :         SOS7ImpExp                  char *GetHost ( );
public     :         SOS7ImpExp                  int16 GetLastError ( );
public     :         SOS7ImpExp                  uint32 GetPort ( );
public     :                                     void Initialize ( );
protected  :                                     SOCKET InternalConnect ( );
public     : virtual SOS7ImpExp                                          ~CS_Client ( );
};

#pragma pack()
#endif
