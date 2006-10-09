/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    CS_ServerHelper

\brief    


\date     $Date: 2006/03/12 19:21:28,98 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CS_ServerHelper"

#include  <pdefault.h>
#include  <sCS_Connection.hpp>
#include  <sCS_Server.hpp>
#include  <stim.hpp>
#include  <swinsock.hpp>
#include  <sCS_ServerHelper.hpp>


/******************************************************************************/
/**
\brief  HandshakeThread

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HandshakeThread"

logical CS_ServerHelper :: HandshakeThread ( )
{
  logical                 term = NO;
  logical                 newclient= NO;
  CS_ServerClient        *client= NULL;
BEGINSEQ
//BOOL b= YES;
//setsockopt( sock, IPPROTO_TCP, TCP_NODELAY, (char*) &b, sizeof( b ) );

// now identify c/s
char buf[1024];
strcpy( buf+4, "HALLO-ODABA2-CLIENT" );
int32 sl= strlen( buf+4 ) + 1;
*((int32 *) buf)= htonl(sl);
if( CS_Connection::sock_send( sock, buf, sl + 4, term ) ) ERROR
if( CS_Connection::sock_recv( sock, &sl, 4, term ) ) ERROR
sl = ntohl( sl );
if( sl > 256 ) ERROR
if( CS_Connection::sock_recv( sock, buf, sl, term ) ) ERROR
if( strcmp( buf, "HALLO-ODABA2-SERVER" ) != 0 ) ERROR
int32 cid;
if( CS_Connection::sock_recv( sock, &cid, 4, term ) ) ERROR

if( cid == -1 )
{
    int64 s2= sock;
    if( CS_Connection::sock_send( sock, &s2, 8, term ) ) ERROR
    LEAVESEQ
}
else
if( cid == 0 )
{
    if ( !(client= server->CreateClient()) )         ERROR
    newclient= YES;    
    if( CS_Connection::sock_send( sock, &client->connect_id, 4, term ) ) ERROR
    if( CS_Connection::sock_send( sock, &server->server_id, 8, term ) ) ERROR    
}
else
{
    int64 sid;
    if( CS_Connection::sock_recv( sock, &sid, 8, term ) ) ERROR
    client= server->FindClient( cid );
    if( sid != server->server_id || client == NULL )
    {
        cid= 0;
        CS_Connection::sock_send( sock, &cid, 4, term );
        ERROR
    }
    cid= client->connect_id;
    if( CS_Connection::sock_send( sock, &cid, 4, term ) ) ERROR
}
int64 s2;
if( CS_Connection::sock_recv( sock, &s2, 8, term ) )
{
    client= NULL;
    ERROR
}
client->HandshakeS( sock, (SOCKET) s2 );

if( newclient )
{
  server->AddClient( client );    
  client->StartThreads();
}
RECOVER
  if( newclient ) delete client;
  shutdown( sock, 2 );
  closesocket( sock );
  term = YES;
ENDSEQ
delete this;
  return(term);
}


