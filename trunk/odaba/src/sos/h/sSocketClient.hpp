/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    SocketClient

\brief    


\date     $Date: 2006/06/29 15:53:48,32 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SocketClient_HPP
#define   SocketClient_HPP

#include "csosdll.h"
class     SocketClient;

#include  <sSocket.hpp>
#include  <standard.hpp>
class  SocketClient :protected Socket
{
protected  :         std_string                                   host;                                                      // 
protected  :         int32                                        port;                                                      // 

public     :
                     std_string                                  &get_host() { return(host); }
                     int32                                        get_port() { return(port); }
public     :                  SOSImpExp             logical Connect (std_string shost, int32 port_number );
public     :                  SOSImpExp             logical Connect ( );
public     :                                        logical GetResponse (std::string &std_str );
public     : virtual                                int32 Receive (std_string &rSBuffer ) const;
public     :                                        logical Response (int32 responsecode );
public     :                                        logical Response (std_string sCode );
public     :                  SOSImpExp             logical SetHost (std_string shost );
public     :                  SOSImpExp             logical SetPort (int32 port_number );
public     :                  SOSImpExp                  SocketClient (std_string shost, int32 port_number );
public     :                  SOSImpExp             const SocketClient &operator<< (const std_string cSBuffer ) const;
public     :                  SOSImpExp             const SocketClient &operator<< (int32 intval ) const;
public     :                  SOSImpExp             const SocketClient &operator>> (std_string &rSBuffer ) const;
public     : virtual          SOSImpExp                  ~SocketClient ( );
};

#endif
