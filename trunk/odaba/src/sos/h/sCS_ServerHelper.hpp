/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    CS_ServerHelper

\brief    


\date     $Date: 2006/03/12 19:19:47,18 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CS_ServerHelper_HPP
#define   CS_ServerHelper_HPP

class     CS_ServerHelper;

class     CS_Server;
#include  <swinsock.hpp>
#pragma pack(8)

class  CS_ServerHelper
{
public     :         SOCKET                                       sock;                                                      
public     :         CS_Server                                   *server;                                                    

public     :
public     :                                     logical HandshakeThread ( );
};

#pragma pack()
#endif
