/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    Socket

\brief    Socket


\date     $Date: 2006/06/29 15:53:59,33 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   Socket_HPP
#define   Socket_HPP

#include "csosdll.h"
class     Socket;

#define  MAXCONNECTIONS                            5
#define  MAXRECV                                   500
#include  <sSocket.hpp>
#include  <standard.hpp>
class  Socket
{
protected  :         int32                                        sockethandle;                                              // 
protected  :         sockaddr_in                                  addresshandle;                                             // 

public     :
                     int32                                        get_sockethandle() { return(sockethandle); }
                     sockaddr_in                                 &get_addresshandle() { return(addresshandle); }
public     :                                        logical Accept (Socket &rSocket );
public     :                                        logical Bind (const int16 bindport );
public     :                                        logical Connect (const std_string cSHost, const int16 bindport );
public     :                                        logical Create ( );
public     : virtual          SOSImpExp             void Disconnect ( );
public     :                                        logical IsConnected ( ) const;
public     :                                        logical Listen ( ) const;
public     : virtual                                int32 Receive (std_string &rSBuffer ) const;
public     : virtual                                int32 ReceiveBlock (std_string &rSBuffer ) const;
public     : virtual                                logical Send (const std_string cSBuffer ) const;
public     :                  SOSImpExp                  Socket ( );
public     :                                        logical Status ( ) const;
public     : virtual          SOSImpExp                  ~Socket ( );
};

#endif
