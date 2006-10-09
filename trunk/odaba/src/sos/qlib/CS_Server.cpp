/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    CS_Server

\brief    


\date     $Date: 2006/03/12 19:21:27,79 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CS_Server"

#include  <pdefault.h>
#include  <cactp.h>
#include  <cfctp.h>
#include  <ctfctp.h>
#ifndef   DLL_CS_ServerClient_HPP
#define   DLL_CS_ServerClient_HPP
#include  <sCS_ServerClient.hpp>
#include  <sDLL.h>
#endif
#include  <sCS_ServerClient.hpp>
#include  <sCS_ServerHelper.hpp>
#include  <sRessourceLock.hpp>
#include  <sThreadLink.hpp>
#include  <sdttm.hpp>
#include  <stim.hpp>
#include  <swinsock.hpp>
#include  <sCS_Server.hpp>


/******************************************************************************/
/**
\brief  AddClient

\return term - Success

\param  client -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddClient"

logical CS_Server :: AddClient (CS_ServerClient *client )
{
  logical                 term = NO;
  lock->ILock();

  clients->AddTail( client );
  lock->IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  CS_Server


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CS_Server"

                        CS_Server :: CS_Server ( )
                     : vcls (),
  sock(NULL),
  clients(NULL),
  lock(NULL),
  threadTerm(NO),
  nextCID(1),
  last_error(0),
  server_id(0),
  started(NO),
  threadServer(NO),
  term_event()
{

#ifndef __unix__
WSAData d;
WSAStartup( MAKEWORD( 1, 1 ), &d );
#endif

lock = new RessourceLock(NO);

clients= new DLL(CS_ServerClient)();

dttm dm; 
dm.SetCurrent();

server_id= ( dm.get_date().GetLongInt() << 32 ) +
           dm.get_time().GetLongInt();


}

/******************************************************************************/
/**
\brief  CheckTimeout

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckTimeout"

logical CS_Server :: CheckTimeout ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  CreateClient

\return server_client -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateClient"

CS_ServerClient *CS_Server :: CreateClient ( )
{
  CS_ServerClient  *server_client = new CS_ServerClient();

  Initialize(server_client);
  return (server_client);
}

/******************************************************************************/
/**
\brief  FindClient

\return client -

\param  connect_id -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindClient"

CS_ServerClient *CS_Server :: FindClient (uint32 connect_id )
{
  CS_ServerClient*                 client = NULL;
BEGINSEQ
  lock->ILock();

  clients->GoTop();
  while( client= clients->GetNext() )
    if( client->connect_id == connect_id ) LEAVESEQ

  ERROR
RECOVER
  client=NULL;
ENDSEQ
  lock->IUnlock();
  return(client);
}

/******************************************************************************/
/**
\brief  GetLastError - 


\return last_error -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLastError"

int16 CS_Server :: GetLastError ( )
{

return( last_error );

}

/******************************************************************************/
/**
\brief  Initialize - 



\param  server_client -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void CS_Server :: Initialize (CS_ServerClient *server_client )
{

  lock->ILock();

  server_client->server= this;
  server_client->connect_id= ++nextCID;

  lock->IUnlock();

}

/******************************************************************************/
/**
\brief  IsRunning

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsRunning"

logical CS_Server :: IsRunning ( )
{

  return(!threadTerm);

}

/******************************************************************************/
/**
\brief  RemClient

\return term - Success

\param  client -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemClient"

logical CS_Server :: RemClient (CS_ServerClient *client )
{
  logical                 term = NO;
BEGINSEQ
SOSTRY
{
  lock->ILock();
  
  if ( !clients->Find( client ) )                    ERROR
  clients->RemoveAt();
  
  lock->IUnlock();
  
  client->set_shutting_down(YES);
  RemoveClient(client);
}
SOSCATCH
{
  SOSERR(518)
}

RECOVER
  lock->IUnlock();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveClient


\param  client -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveClient"

void CS_Server :: RemoveClient (CS_ServerClient *client )
{



}

/******************************************************************************/
/**
\brief  RemoveClients

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveClients"

logical CS_Server :: RemoveClients ( )
{
  CS_ServerClient*        client = NULL;
  logical                 term = NO;
  lock->ILock();

  clients->GoTop();
  while( client= clients->GetTail() )
    RemClient(client);

  lock->IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  ServerThread

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ServerThread"

logical CS_Server :: ServerThread ( )
{
  logical                 term = NO;
ulong fl= 1;
ioctlsocket( sock, FIONBIO, &fl );

while( !threadTerm )
{
  CheckTimeout();
  if( !CS_Connection::sock_waitfor( sock, 2000, NULL, threadTerm ) && !threadTerm )
  {
    SOCKET s= accept( sock, NULL, NULL );
    if( s != INVALID_SOCKET )
    {
        CS_ServerHelper* sh= new CS_ServerHelper;
        sh->server= this;
        sh->sock= s;
        
        BOOL b= YES;
        setsockopt( sh->sock, IPPROTO_TCP, TCP_NODELAY, (char*) &b, sizeof( b ) );
       
        TLINK(sh,CS_ServerHelper,HandshakeThread).ThreadCall();
    }   
  }
}

  term_event.Set();
  return(term);

}

/******************************************************************************/
/**
\brief  Start

\return rc - Retrun code

\param  wPort -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Start"

int32 CS_Server :: Start (int16 wPort )
{
int32 rc=0;
DEFLOCALERR
BEGINSEQ
sock= socket( AF_INET, SOCK_STREAM, IPPROTO_IP );

#ifdef __unix__
int reuse = 1;
setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
#else
if ( sock == INVALID_SOCKET )
  rc = WSAGetLastError();
#endif

sockaddr_in sa;
memset( &sa, 0, sizeof( sa ) );
	
sa.sin_family= PF_INET;
sa.sin_port= htons( (WORD) wPort );
sa.sin_addr.s_addr= 0; // any

if( bind( sock, (sockaddr*) &sa, sizeof( sa ) ) == SOCKET_ERROR )
    LOCALERR(306)

if( listen( sock, 10 ) == SOCKET_ERROR ) LOCALERR(307)

threadTerm= NO;
threadServer= YES;
TLINK(this,CS_Server,ServerThread).ThreadCall();

RECOVER
  rc = LOCALERROR;
ENDSEQ
  return(rc);
}

/******************************************************************************/
/**
\brief  Stop


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Stop"

void CS_Server :: Stop ( )
{

  RemoveClients();
  
  threadTerm= YES;
  term_event.WaitForSet(AUTO);
//  while( threadServer ) tim::timestp(10);
//  shutdown( sock, 2 );
  closesocket( sock );


}

/******************************************************************************/
/**
\brief  ~CS_Server


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CS_Server"

                        CS_Server :: ~CS_Server ( )
{

  delete clients;
#ifndef __unix__
  WSACleanup();
#endif
  delete lock;

}


